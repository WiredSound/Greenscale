#pragma once

struct Damage {
	int kinetic; // Applies a direct reduction of the component's integrity.
	int thermal; // Adds heat to the component. Some heat can disable the component temporarily while larger amounts can disable it permanently or cause it to explode.
	float disruption; // Liklihood that the component will become disabled temporarily or malfunction.
};