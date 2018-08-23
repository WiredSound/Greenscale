# Programming Project

## Brief

The program I aim to build is a turn-based roguelike game centred around constructing a group of combat robots used to destroy various transmission towers scattered across the game world. The game is inspired by similar titles such as *Cogmind* and *Caves of Qud* as well as the *Blade Runner* movies and the book that said films are based upon, *Do Androids Dream of Electric Sheep?*

I plan to implement this program using modern C++. By "modern" I mean using features such as smart pointers (namely `std::unique_ptr` and `std::shared_ptr`), lambdas, templates and heavy use of the STL. In addition, I plan to use the SFML library for rendering and for some mathematical uses. I chose to use SFML over the most common alternative, SML, as it is designed with C++ and not C in mind (i.e. makes use of object orientated programming). While SFML is most certainly the largest dependency, I will also make use of `nlohmann/json` for the handling of JSON data files, and `FastNoise` for generating simplex fractal noise which is used in procedural level generation. In terms of tools, I will be using Visual Studio C++ 2015 along with the included C++ compiler; notepad++ for editing JSON files; GIMP for creating textures; GitHub Desktop for source control (I find it much nicer to use than command-line git); Google Drive to back up the project; and Typora for writing this very document.

In order to make small changes to the game without making to rebuild the entire project as well as allow player modding, I decided to have all game data exist in JSON data files (which can be seen in the `assets` folder) rather than hard-code such data into the source code itself. I considered implementing a JSON parser but ultimately decided to use a pre-existing library as implementing such a parser could be a entirely different project in and of itself. One potential drawback of this approach is (at least, theoretically) increased loading times when a user starts the game. Compiled C++ is so incredibly quick however, I realised that any increase in start-up time would ultimately be entirely negligible.

## Structure

I have identified seven key sections that will make up the code base: states, components, entities, GUI, game map/world, projectiles and other. These are also the main directories found in the `src` folder (aside from all files considered "other" which are found just in `src` itself). Below I will go other the meaning of each of these categories as well as the more vital pieces of code, templates and classes found in them.

### States (`src/states/`)

#### `State` (`State.h`)

I decided to based the core of the game around a state system in order to separate key parts such as the main menu, options menu and the game itself. The `State` class holds a protected reference to the `sf::RenderWindow` so that drawing to the window can take place and the mouse position can be fetched. This class also has two public pure virtual methods `void update(Input &input)` and `void draw()` which must be overridden by all subclasses of `State`. The `update` method handles input and updates game logic while `draw` is tasked with drawing to the screen.

#### `GameState : State` (`GameState.h`, `GameState.cpp`)

This is where the bulk of the program takes place. `GameState` overrides both the `update` and `draw` methods of its superclass `State`. It also takes references to the window, text font and game settings in its constructor with the first passed to the super constructor and the later two kept as private members.The constructor is also tasked with setting up the `GameGui` and ensuring the instance of the `Console` class has a reference to GUI console window. The private `world` and `camera` members are also initialised here.

In the overridden `update` method, first the world's update method is called, followed by the GUI's and finally the camera's. In the overridden `draw` method, the game world and GUI are drawn.

### Other (`src/`)

#### `main.cpp`

The first task performed in `main` is loaded the game settings from the `options.json` file. This is handled by the `GameSettings loadSettings(std::string filename)` function which returns a `GameSettings` struct (defined in `GameSettings.h`). Next an `sf::RenderWindow` of the size specified in the options file is created and whether that window is full-screen and has V-sync enabled is also set based upon the options file. The font stored in `assets/font` is also loaded and an `sf::Clock` is created in order to measure the frames per second the game is running at. A unique pointer to an instance of the `GameState` class is created as well as an instance of `Input` and then the game loop is entered (and continues looping until the window is closed).

The game loop begins by checking if the `sf::Event::Closed` event has occurred by calling `input.update()`. That method returns true if that event has indeed been generated and if it has the window is then closed. If such an event has not been generated then the `update` method of the current `State` is called. Next, the window is cleared and the current `State`'s `draw` method is called. Finally, the current FPS is calculated (by counting how many loops go by in one second) before the render buffers are swapped with a call to `window.display()`.

#### `Camera` (`Camera.h`, `Camera.cpp`)

The `Camera` class is tasked with handling changes to the render window's `sf::View` instance in order to move the camera around the world space. It also handles smoothly moving the view to a target point in space (via the `moveTowardsCentre` method) as well as ensuring the GUI remains static.

#### `Console` (`Console.h`, `Console.cpp`)

The class `Console` allows messages of a specific type (be it a warning, information, etc.) to be written to `stdout` as well as shown on the GUI console. It also has a nested class (functioning essentially as an enum but with members) called `MessageType`. Each `MessageType` has a `name` of `std::string` type and a `colour` of `sf::Color` type. The class has five defined constant message types (and note that no more can be added as the constructor to `MessageType` is private) which are `INFO`, `INFO_NONESSENTIAL`, `WARNING`, `FATAL` and `SPEECH`.

The `Console` class has one primary method: `void display(Message msg, bool guiPrependMsgType = false)`. This method takes a `Message` (which is just a struct containing some text and a message type) displays it on the GUI console or, if no console GUI is specified, to `stdout`. The boolean `guiPrependMsgType` (which defaults to `false`) specifies whether the type of message should also be displayed alongside the message text on the GUI console (note that the message type is always displayed when writing to `stdout` as messages cannot be colour-coded there).

#### `IDs` (`IDs.h`)

In `IDs.h` there are various enums defined within the `IDs` namespace. These enums include IDs for tiles, components, component upgrades, entities and projectiles.

#### `Manager` (`Manager.h`)

`Manager` is a class template that is designed to make the loading of tiles, projectiles, etc. from JSON files easier. The template requires two types to be specified: `Key` which is typically an enum stored in the `IDs` namespace and `Managed` which is an object storing all the data relevant to what is being managed (for example, `EntityInfo` for `EntityManager` or `Tile` for `TileManager`). This class also has two pure virtual methods which must be override: `void parseJson(nlohmann::json json)` which is where any general information in the JSON file can be loaded (for example, the dimensions of a single texture frame in the case of `EntityManager`) and `std::pair<Key, const Managed> parseJsonManaged(nlohmann::json json)` which is where pairs between the keys and their associate managed objects are made.

#### `TurnManager` (`TurnManager.h`, `TurnManager.cpp`)

Note that although this class is called `TurnManager`, it does not inherit from `Manager`. It is for that reason that I may ultimately change the name of the `TurnManager` class (perhaps to `TurnHandler` or `TurnDistributor`?)

The game is of course turn-based so it is the role of the `TurnManager` class to handle the turn system. It takes a `GameMap` reference in its update function and then fetches all the entities present on that map. Each turn for an entity is split into several distinct phases:

 * First, the entity's `yourTurnBegin` method is called once.
 * Next, `yourTurnDecision` is called which in turn calls upon the entity's controller. This method is called every frame until `true `is returned which indicates that the controller has at that point decided what the entity will do this turn.
 * The next method called by the turn manager is `yourTurnCurrently` which is where the entity actually carries out their action (whether that may be attacking, moving, etc). This is again called continually until `true` is returned.
 * Finally, the entity's `yourTurnEnd` method is called once before the turn manager moves on to the next entity.

#### `Animation` (`Animation.h`, `Animation.cpp`)

The `Animation` class handles all the frames that make up an animation. The nested `Frame` struct stores the coordinates of each frame as well as its colour (which is ignored should one not be specified). The public method `getFrame` allows the caller to fetch what would be the appropriate frame at the time specified. By not having any timing take place in the `Animation` class itself, this means that an animation can be shared between multiple entities even if each entity is at a different point in the animation.

#### `Input` (`Input.h`, `Input.cpp`)

I created the `Input` class after I realised that SFML provided no easy why to check if a key had pressed just in the last frame. This class makes it simpler to know which keys and mouse buttons are held and which have been immediately just pressed. It also provides the position of the mouse relative to the game window which simply calling `sf::Mouse::getPosition()` does not account for.

### Map (`src/map/`)

#### `World` (`World.h`, `World.cpp`)

The game world is made of a grid of different game maps. Only one game map is loaded and drawn at a time but it will possible for players to move between maps via a map GUI or by moving to the furthest edge of the map their currently in.

#### `GameMap` (`GameMap.h`, `GameMap.cpp`)

The `GameMap` is were all map information (such as entities present, tiles and projectiles) is stored and also where the rendering of this information takes place. I may at some point move the rendering code out into its `GameMapRenderer` class as that would allow easy changes to how a map is displayed regardless of what data said map contains.

The map has two important private members: a unique pointer to a `TileLayer` called `tiles` and a unique pointer to an `EntityLayer` called `entities`. As you would expect, `tiles` stores the grid of tiles that makes up a map as well as draws said tiles while `entities` stores and draws all the entities present on this grid. The game map is also tasked with the storage and rendering of all `ProjectileArc` instances which may be generated by entities.

#### `MapBuilder` (`MapBuilder.h`, `MapBuilder.cpp`)

This class handles the construction of a new `GameMap` instance and also performs all the processes required to do so. This includes loading all the required textures from the assets folder, building tile and entity layers, calling map generators, adding the initial group and entities, and finally actually building and returning a unique pointer to an instance of `GameMap`.

#### `MapLayer : sf::Drawable` (`MapLayer.h`, `MapLayer.cpp`)

The `MapLayer` class handles the drawing of map data (eg. tiles or entities) through maintaining an `sf::VertexArray`. It has two primary subclasses: `TileLayer` and `EntityLayer`.

#### `TileLayer : MapLayer` (`TileLayer.h`, `TileLayer.cpp`)

All tile data is stored as a unique pointer to an array containing may `TileColourOrientation` structs called `tiles`. `TileColourOrientation` is a struct defined within `TileLayer` that simply hold a tile id, colour and orientation. The tile layer also holds the only instance to `TileManager` so that all the relevant data related to a tile can be fetched based on its ID.

#### `Entity Layer : MapLayer` (`EntityLayer.h`, `EntityLayer.cpp`)

The `EntityLayer` stores all entities as a `std::vector` containing shared pointers to instances of `Entity`. I spent quite some time deciding as to whether entities should be held by unique pointers or shared pointers. I decided on shared pointers as it meant that it was possible to return a small subset of entities from methods like in `getEntitiesAt` and `getEntitiesOver`. This would not be possible were they stored as unique pointers as a vector cannot contain references (and the unique pointers themselves obviously cannot be used as only the entity layer has ownership of them). It also made it easier to have entities that were shared between all maps without having to manually transfer ownership between each map.

One rather important thing to note is that the `addEntity` method does not appropriately set the entity's pointer to the `GameMap` it is in. The correct way to add a new entity to the map is via `GameMap::addEntity` as that method ensures that the entity has a raw pointer to the map (the reason it is a raw pointer is because it is set via the `this` keyword).

#### `MovementPath` (`pathfinding/MovementPath.h`, `pathfinding/MovementPath.cpp`)

The `MovementPath` class stores points on a grid making up a path that an entity or projectile can follow. These points are stored as `sf::Vector2u` instances in a `std::vector`. A `MovementPath` is also capable of holding a current position which can be incremented via `nextPosition`.

There are also two static methods defined in `MovementPath`: `buildLinePath` and `distanceFromTo`. The `buildLinePath` method simple constructs a straight path between two points. It does this simple wrapping the collection of points returned by `GridHelp::buildLine` into a `MovementPath`. The `distanceFromTo` returns how many tiles are between two points when traveling in a straight line. Again this uses `GridHelp::buildLine` but instead returns the number of points returned by that function.

#### `AStarPathBuilder` (`pathfinding/AStarPathBuilder.h`, `pathfinding/AStarPathBuilder.cpp`)

The `buildAStarPath` uses my implementation of the A* pathfinding algorithm to building a path connecting two points while taking into account places on the map that entities cannot walk over. Unlike the path building methods in `MovementPath`, `buildAStarPath` is not static and the `AStarPathBuilder` has to be initialised with a pointer to the `GameMap`. Note that should some code need pathfinding, it does not need to build its own instance of the pathfinder as all game maps have a publicly-accessible instance of `AStarPathBuilder` simply called `pathfinder`.

#### `MapGenerator` (`generators/MapGenerator.h`)

The `MapGenerator` class, which has just two overridable methods, allows for the tiles and entities that make a game map to be procedurally generated. Note that this is distinct from `MapBuilder` which is simply tasked with constructing the tile and entities layers needed by a map followed be an actually instance of `GameMap`. When building a map using `MapBuilder::buildMap` the caller can specify multiple map generators which are tasked with the actual generation. All map generators have a protected instance of the `Random` class as well as `generateTiles` and `generateEntities` methods.

### Entities (`src/entities/`)

#### `Entity` (`Entity.h`, `Entity.cpp`)

The `Entity` class handles all the actions an entity makes and how it interacts with the `GameMap` it is located in. The ID of the entity determines the animation, default components, name, description and other such static values held in the relevant `EntityInfo` struct contained in the `EntityManager`. Values that vary between entities, such as the current equipped components, aligned factions, position, as well as the behaviour (primarily via the held `EntityController` shared pointer) are stored in the Entity class itself.

All entities have their own grid of components (instance of `ComponentGrid`) where they can equip and use any components that they encounter in-game. An entity's current and maximum integrity is equivalent to sum of the current and maximum integrity of each of its components respectively. Entities also have controllers which are called upon to manage their behaviour each turn. I decided to have the entities themselves separate from their controllers as it makes it simple to change how an entity acts without having to perform any real changes to the entity itself (for example, any entity can be given a pointer to `PlayerController` which allows the player to control that entity without performing any changes to the type or state of the entity).

#### `Robot : Entity` (`Robot.h`, `Robot.cpp`)

Robots are defined as a specific type entity with the three animation states: idle, moving and destroyed. The `Robot` class overrides the `Animation::Frame fetchFrame()` method of its parent and returns the appropriate current frame of animation base on the entity's state. The `sf::Color getColour()` is also overridden and returns the pulsating 'my turn' colour if it is the robot's turn, otherwise the colour of the robot's faction is returned.

#### `EntityBuilder` (`EntityBuilder.h`, `EntityBuilder.cpp`)

The `EntityBuilder` is tasked with loading all the data required by the entity manager as well as constructing new entities through its `buildEntity` method.

#### `EntityManager : Manager<IDs::Entities, EntityInfo>` (`EntityManager.h`, `EntityManager.cpp`)

All data relating to entity types that does not change (eg. animations, name, description, etc.) is stored in the `EntityManager` as a `EntityInfo` struct with an associated `IDs::Entity`. This information is, using the `Manager` template class, loaded from a JSON file.

#### `Faction` (`Faction.h`, `Faction.cpp`)

The faction system is currently very simple but I plan to later improve it by allowing each faction to have a varying opinion of every other faction which can begin to change as the player interacts with the game world.

`Faction`, though defined as a class, is essentially an improved enum (very similar to the type of enums that can be defined in newer versions of Java). Each faction has a name, a short-hand name, a colour and a priority - the priority determines what order entities have their turns. The constructor to `Faction` is private and there are four static constant factions already defined: `UNALIGNED`, `PLAYER`, `ROGUE`, `CORPORATION`. The `==` operator is also defined so that factions can be compared for equality.

#### `EntityController` (`controllers/EntityController.h`)

The `EntityController` is a class with just one pure virtual method: `bool handle(Entity *entity, Input &input)` which is called upon by entities in order to control them (either by the player or some sort of AI). Originally, there were separate `handleMovement` and `handleAttacking` methods as an entity could both move and perform an action per turn. Now however movement counts as one of the actions an entity is allowed to perform per turn (note that this is not yet properly enforced so a controller could potentially be written that performs multiple actions in a turn - this is something I will likely address at a later point).

In the `src/entities/controllers/` directory are a few different entity controllers each with fairly self-explanatory functionality.

### Components (`src/components/`)

#### `Component` (`Component.h`, `Component.cpp`)

Components function in the game as the equippable items used to customise the functionality of entities. Components can perform actions or modify stats on a per-turn basis as well as when they are used. There are also various upgrades that can be added to modify the effects and stats of components.

The base stats of each component are defined in a JSON file and stored in the component manager as `ComponentInfo` structs. One of the more vital elements of these structs is their `std::string type` value which determines which `Component` subclass that component is designed to be initialised as.

`Component` has a method `const ComponenInfo &fetchInfo()` which calls upon the `EntityManager` to get the base stats (no upgrades applied) of this component based on its `id` value. There are also various getter methods defined that fetch the values returned by `fetchInfo` but only after the relevant upgrades have been applied to them. The application of these upgrades is handled by a private template function called `statWithUpgradesApplied`. It takes the base value of the stat as well as the modifier type (thorough a `ModifierFunc` callable) and iterates through each upgrade applying the specified changes to the base value. An exemplary usage of this can be seen by `getMaxIntegrity` which returns `statWithUpgradesApplied<unsigned int>(fetchInfo().maxIntegrity, integrityModifier)` where `integrityModifer` is a simple lambda expression that returns an upgrade's integrity modifier: `[](auto &upgrade) { return upgrade.maxIntegrityModifier; }`. This lambda-based approach replaced a rather ugly and confusing macro that was used for this purpose previously.

Two important methods of `Component` are `yourTurn` and `use`. The `yourTurn(Entity &entity, PowerPool &pool, Console &console)` method begins by decreasing the value of `disabledForTurns` and then checking if the component is enabled (meaning it is both manually enabled and has not been disabled due to heat or any other such reason). If it is indeed enabled, then the power in the passed `PowerPool` is increased assuming this component generates any power on a per-turn/passive basis. The component's heat is also increased should the component generate heat passively. If there is enough power available in the pool, then the `yourTurnEnabled` method is called. If there is not enough power then the component is disabled. Regardless of whether the component is currently enabled, it has a random chance to become disabled if it is at a dangerous or fatal heat level.

The virtual method `yourTurnEnabled`, by default, drains the power pool based on the component's passive power consumption and dissipates heat based on the component's passive heat dissipation value. This method can overridden by components with more complex behaviour to perform per turn.

The `std::vector<ProjectileArc> use(Entity &user, MovementPath path, PowerPool &pool, Console &console)` is called when an entity decides to use their turn by activating this component. If the component is enabled and has the required power then `useEnabled` is called and its return value is also returned. Should the entity wish to fire any projectiles (such as in `RangedComponent`) then it should build a `std::vector` containing `ProjectileArc` objects and return it from `useEnabled`.

The main other types of components at the moment are `RangedComponent` and `SpawnerComponent` with the former shooting projectiles on use and the later capable of spawning new entities.

#### `ComponentBuilder` (`ComponentBuilder.h`, `ComponentBuilder.cpp`)

The `ComponentBuilder` loads both the component and projectile managers and has methods for the construction of new `Component` objects. Method `buildComponentNoUpgrade`, as the name would suggest, constructs a new component (encapsulated in a unique pointer) of the given `id` with no additional upgrades. There is also a `buildComponentRandomised` which is currently unimplemented but should construct a component with random compatible upgrades within a value totalling `upgradePoints`.

#### `PowerPool` (`PowerPool.h`, `PowerPool.cpp`)

The component system is based around each entity having a certain power level. Some components may consume power while other may generate it (either on use or per turn). All of this power is stored in the entity's power pool. `PowerPool` has `increasePower` and `decreasePower` methods which modify the power level by the given amount without letting it exceed the maximum amount of power storage (`ComponentGrid::getMaxPowerStorage`) or go between 0. It also has the `hasSufficientPower` method which checks if there is equal or more power available than the value specified.

### GUI (`src/gui/`)

Implementing a decent GUI system that was extendable and compatible with different window resolutions proved rather challenging (and, to be honest, I have not reached a point yet where I am completely satisfied with the GUI system). The current system is based around a child/parent structure with any `Gui` capable of having however many child `Gui` objects. The position and size of every GUI element is specified as a fraction of its parent's position and size with the exception of `RootGui` which fills the entire window.

GUI elements also have methods `mouseHover` and `mouseNotHovering` which can be overridden in order to perform certain behaviours based on the mouse position (this is seen in `GuiWindow` which changes its background colour based on whether the mouse is hovering over it).

#### `Gui : sf::Drawable, sf::Transformable` (`Gui.h`, `Gui.cpp`)

The `Gui` class is setup to have a collection of other `Gui` children and has updating and drawing methods. It also has two pure virtual methods: `sf::Vector2f getAbsolutePosition()` and `sf::Vector2f getAbsoluteSize()`. These methods are overridden by `RootGui` (which just returns a position of (0, 0) and the size of the window it occupies) and `ChildGui` (which returns a position and size based upon the position and size of its parent).

#### `ChildGui : Gui` (`ChildGui.h`, `ChildGui.cpp`)

`ChildGui` inherits from `Gui` but most notably overrides the pure virtual methods `getAbsolutePosition` and `getAbsoluteSize`. Each child GUI element has a relative position and size expressed as floating-point vectors. The absolute position and size of a child GUI element is determined as each absolute value of the element's parent multiplied by the appropriate relative value. For example, a child with the relative position (0.25, 0.5) and a parent that has the size (1000, 1000), will have the absolute position (250, 500).

### Projectiles (`src/projectiles/`)

#### `ProjectileArc` (`ProjectileArc.h`, `ProjectileArc.cpp`)

Projectiles that may be fired by weapons are represented as instances of the `ProjectileArc` class. Each projectile arc has a `Damage` value that is inflicted should the projectile hit an entity target as well as a penetration value which indicates what strength of blocking tile the projectile can destroy. The ID of the projectile arc is used to fetch all the visual information (`ProjectileVisual` struct) required from the `ProjectileManager`. The rendering of projectiles is handled by `GameMap` and not by any projectile arcs themselves.

## Code

I would include the source code in this document but it consists of over 8,000 lines across hundreds of different files! It can instead by viewed on my GitHub: https://github.com/WiredSound/Greenscale