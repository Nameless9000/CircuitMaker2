# CircuitMaker2
Development for a c++ to Circuit Maker 2 save string generator.
Game Link: https://www.roblox.com/games/6652606416/Circuit-Maker-2

## How to use:
To use this you need to know C++. Currently the SDK is in development so will be major breaking changes.

### Setting it up
To start off a project you need to include the sdk and initialize the node data

```c++
// include the sdk
#include "sdk.hpp"

void main() {
  // initialize the node data
  NodeData node_data = NodeData();
}
```

### Creating blocks
To create a block you can the following:
```c++
NodeData::create<NodeType T>(NodePosition position, bool state, std::vector<short> properties);
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
NodeRef led = node_data.create<AND>({}, true);
// create a BUTTON block
NodeRef button = node_data.create<BUTTON>();

// connect the button to the led
button >> led;
```

### Finishing things off
To finish and compile the save string you can use
```c++
NodeData::compile(char max_x = 5, char max_z = 5)
```
It will return an `std::string` for you to print or save.
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
Currently there are the "Memory" and "Plexers" modules (may be out of date at time of reading), they can be used to auto-generate things like Registers.
If you would like a full list of what you can do then you can view the header files (*.hpp) inside `/Development/SDK`

An example of using one:
```c++
NodeData node_data = NodeData();

Memory::MemoryCell memory_cell = Memory::MemoryCell(&node_data);

memory_cell.input_bit
  << node_data.create<FLIPFLOP>(NodePosition{ 1, 5, 0 });

memory_cell.output_bit
  >> node_data.create<LED>(NodePosition{ 2, 5, 0 }, true);

memory_cell.update_bit
  << node_data.create<BUTTON>(NodePosition{ 3, 5, 0 });

std::cout << node_data.compile();
```
