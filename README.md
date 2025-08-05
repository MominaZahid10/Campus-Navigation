# Campus Navigation System

A comprehensive C++ application for navigating and managing campus locations at GIKI (Ghulam Ishaq Khan Institute). This system implements multiple data structures to provide efficient campus navigation, building management, and route optimization.

## Features

### 🏢 Campus Hierarchy Management
- **Tree Structure**: Displays the complete campus hierarchy using a binary tree
- **Building Search**: Find specific buildings and their information
- **Keyword Recommendations**: Get building suggestions based on keywords (sports, health, hostel, cafe)

### 🗺️ Path Finding & Navigation
- **Shortest Path Algorithm**: Uses Dijkstra's algorithm to find optimal routes between locations
- **Dynamic Location Management**: Add new locations and connect them to existing ones
- **Connection Visualization**: View all building connections with travel times

### 📋 Request Management
- **Priority Queue System**: Manages navigation requests with urgent request handling
- **Navigation History**: Track and backtrack through previous navigation routes
- **Request Processing**: FIFO queue for regular requests, priority handling for urgent ones

## Data Structures Used

| Data Structure | Purpose | Implementation |
|----------------|---------|---------------|
| **Binary Tree** | Campus hierarchy and building information | Custom TreeNode structure |
| **Hash Table** | Fast location lookup and storage | Linear probing for collision resolution |
| **Adjacency List** | Graph representation for campus connections | Linked list implementation |
| **Priority Queue** | Navigation request management | Custom queue with urgent request priority |
| **Stack** | Navigation history tracking | LIFO structure for backtracking |
| **Graph (Weighted)** | Campus map with travel times | Adjacency list with weighted edges |

## System Architecture

```
Campus Navigation System
├── Building Management (Binary Tree)
├── Location Storage (Hash Table)
├── Path Network (Weighted Graph)
├── Request Queue (Priority Queue)
└── Navigation History (Stack)
```

## Getting Started

### Prerequisites
- C++ compiler (GCC 7.0+ or equivalent)
- Standard C++ libraries
- Terminal/Command prompt

### Compilation
```bash
g++ -o campus_navigation DSA_project.cpp
```

### Running the Application
```bash
./campus_navigation
```

## Usage Guide

### Main Menu Options

1. **View Campus Hierarchy** - Display the complete building structure
2. **Show Connections** - View all location connections with travel times
3. **Find Shortest Path** - Calculate optimal routes between any two locations
4. **Add New Location** - Dynamically add new campus locations
5. **Add Navigation Request** - Queue navigation requests (with priority support)
6. **Process Navigation Request** - Handle queued navigation requests
7. **Backtrack Navigation** - Return to previous locations
8. **Recommend Buildings** - Find buildings by keyword search
9. **Search** - Find specific buildings and their details
0. **Exit** - Close the application

### Example Usage

#### Finding Shortest Path
```
Enter starting location: Main Gate
```
Output displays shortest distances to all reachable locations.

#### Adding New Location
```
Enter new location: New Lab
Enter the location to connect to New Lab: Academic Block
Enter the time taken to get to New Lab from Academic Block: 5
```

#### Building Recommendations
```
Enter keyword for building search: sports
```
Returns all buildings containing "sports" in their description.

## Campus Locations

### Pre-configured Locations
- Main Gate, Academic Block, Library, FES, FCSE, FME, FCE
- Sports Ground, Sports Complex, Gym, Swimming Pool, Basketball Court
- Boys Hostels, Girls Hostels, Hostel 7, Hostel 8, Hostel 12, Hostel 13
- TUC Area, Raju Cafe, Ayaan Cafe, Medical Center
- LOGIK, Auditorium, Incubation Center, Guest House
- Admin Block, Brabers Building, HBL Bank

### Building Categories
- **Academic**: FES, FCSE, FME, FCE, ACB, Library
- **Administrative**: Admin Block, Brabers Building
- **Residential**: Various hostels with mess and common rooms
- **Recreation**: Sports facilities, cafes, TUC area
- **Services**: Medical Center, Bank, Guest House

## Technical Details

### Algorithms Implemented
- **Dijkstra's Algorithm**: For shortest path calculation
- **Hash Function**: String-based hashing for location storage
- **Tree Traversal**: In-order traversal for hierarchy display
- **Linear Probing**: Hash collision resolution

### Performance Characteristics
- **Location Lookup**: O(1) average case with hash table
- **Shortest Path**: O(V²) time complexity using Dijkstra's algorithm
- **Building Search**: O(n) for tree traversal
- **Request Processing**: O(1) for queue operations

### Memory Management
- Dynamic memory allocation for tree nodes and graph connections
- Proper memory deallocation to prevent memory leaks
- Efficient string handling with C++ STL

## Code Structure

```cpp
// Main Components
struct TreeNode          // Building hierarchy
struct Queue            // Navigation requests
struct Stack            // Navigation history  
class Campus            // Main campus management
struct node             // Graph adjacency list
```

## Color Coding

The application uses ANSI color codes for better user experience:
- **Green** (`\033[32m`): Success messages and headers
- **Red** (`\033[31m`): Error messages
- **Yellow** (`\033[33m`): Location names
- **Cyan** (`\033[36m`): Connected locations

## Future Enhancements

- [ ] GUI implementation using Qt or similar framework
- [ ] Real-time GPS integration
- [ ] Mobile app development
- [ ] Advanced pathfinding algorithms (A*, Floyd-Warshall)
- [ ] Database integration for persistent storage
- [ ] User authentication and personalized routes
- [ ] Traffic simulation and dynamic route adjustment

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is part of a Data Structures and Algorithms course project.


## Acknowledgments

- GIKI Institute for campus layout inspiration
- Data Structures and Algorithms course instructors
- C++ STL documentation and community

---

*Built with ❤️ for efficient campus navigation*
