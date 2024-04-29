# CircuitMaker2
Development for a c++ to Circuit Maker 2 save string generator.
Game Link: https://www.roblox.com/games/6652606416/Circuit-Maker-2

## How to use:
Currently the library is in development so will be major breaking changes.
So don't make anything too insane unless you're ready to change things once you update.

Prerequisites:
- You need to know C++...
- How to add a static library
- (optional) Visual Studio

### Setting it up
There are 2 main ways to use the library:
1. Use a pre-compiled .lib file for the library
2. Add a reference to the cm2cpp project in visual studio (easiest + you can change anything)

Once you have set it up and made sure you can reference things correctly you can start.

To start a creation you can write something like this:
```c++
// include the sdk
#include "sdk.h"

void main() {
  // initialize the node data
  NodeData node_data = NodeData();
}
```

### Creating blocks
To create a block you can the following:
```c++
NodeData::create<NodeType T>(NodePosition position, bool dont_optimize, bool state, std::vector<short> properties);
```
This function returns a `NodeRef` type, the main type that should be used for blocks.
If you do not specify the `NodePosition position` (you can put it as a vector of chars) it will be automatically generated.

### Connections
To create a connection you can use `>>` or `<<` for example:
```c++
// initialize the node data
NodeData node_data = NodeData();

// create an LED block
// the ({}, true) sets the position to automatic and disables optimization
NodeRef led = node_data.create<LED>({}, true);
// create a BUTTON block
NodeRef button = node_data.create<BUTTON>();

// connect the button to the led
button >> led;
```

### Finishing things off
To finish and compile the save string you can use
```c++
NodeData::compile(bool no_debug, bool compile_for_speed, bool optimize_positions, short max_x, short max_z)
```
It will return an `std::string` for you to print or save.
`no_debug` removes the compilation stats
`compile_for_speed` replaced OR and LEDs with NODES
`optimize_positions` will put all the auto-generated positions in 1 spot reducing save size
The `max_x` and `max_z` are for the auto-generated block positions, it will generate a tower with those dimensions.

Example:
```c++
// initialize the node data
NodeData node_data = NodeData();

// create a RANDOM block
node_data.create<RANDOM>();

// print the compiled string
std::cout << node_data.compile();
```

## Modules:
Currently there are the Memory, Plexers, Arithmetic, and Fun modules (may be out of date at time of reading), they can be used to auto-generate things like Registers.
If you would like a full list of what you can do then you can view the header files (*.h) inside the `cm2cpp` solution

Here is a commented version of one of the tests using Memory::MemoryCell
```c++
// include the sdk
#include "sdk.h"

void main() {
	// initialize the node data (save file)
	NodeData node_data = NodeData();

	// create a memory cell inside that node data (it will be an auto generated position)
	Memory::MemoryCell memory_cell = Memory::MemoryCell(&node_data);

	// connect an input
	memory_cell.input_bit
	  << node_data.create<FLIPFLOP>(NodePosition{ 1, 5, 0 });

	// connect and output
	memory_cell.output_bit
	  >> node_data.create<LED>(NodePosition{ 2, 5, 0 }, true);

	// add an update button
	memory_cell.update_bit
	  << node_data.create<BUTTON>(NodePosition{ 3, 5, 0 });

	// output the save to the console
	std::cout << node_data.compile();
}
```
