# Algorithm Visualizer: A Deep Dive into Sorting, Graphs, and Trees
### *Visualize, Understand, and Master Complex Algorithms with Qt*

---

## 1. Introduction
The **Algorithm Visualizer** is an educational tool built with **C++** and the **Qt Framework** designed to bring abstract computer science concepts to life. By transforming complex logic into real-time animations, this project provides a "behind-the-scenes" look at how data structures are manipulated.

**Key Features:**

* **Dynamic Sorting:** Visualize array-based sorting with real-time bar manipulations.* 
* **Graph Theory Sandbox:** Manually place nodes and construct edges to visualize Shortest Path and Spanning Tree algorithms.
 
* **Binary Tree Layout:** Automatically converts comma-separated integer inputs into a hierarchical tree structure using array-based mapping ($2i+1$ and $2i+2$).
* **Live Traversal:** Step-by-step coloring of nodes during Inorder, Preorder, and Postorder traversals.
 
* **Performance Metrics:** Real-time LCD counters to track the time complexity and execution speed of each algorithm.

---

## 2. Watch Visualizer





## 3. User Instructions
Follow these steps to explore the visualizer:

1.  **Navigation:** Use the main menu to switch between Sorting, Graph, and Tree pages.
2.  **For example in Tree Visualizer:**
    * Click the **Input** button on the Tree page.
    * Enter up to 50 integers separated by commas (e.g., `10, 20, 30, 40, 50`).
    * The first integer becomes the root, and subsequent values follow binary tree array-representation rules.
3.  **Algorithm Selection:** Choose the desired algorithm (e.g., Inorder) from the ComboBox.
4.  **Simulation Control:**
    * Adjust the **Interval** spinbox to change the animation speed.
    * Press **Start** to begin (nodes will reset to their default color before starting).
    * Press **Stop** to halt the animation at any time.
5.  **Terminal Feedback:** The final traversal sequence is printed to the terminal console for verification.

---

## 4. Developer Instructions
### Prerequisites
* **Qt Framework:** 6.x or higher (Widgets module).
* **Compiler:** MinGW 64-bit or MSVC.
* **Build System:** CMake.

### Setup
1.  Clone the repository:
    ```bash
    git clone [https://github.com/AntaraAn/AlgoVisualizer.git](https://github.com/AntaraAn/AlgoVisualizer.git)
    ```
2.  Open `CMakeLists.txt` file in **Qt Creator**.
3.  Ensure the console output is enabled in your configuration to see the traversal logs.
4.  Build and run the project using `Ctrl + R`.

---

## 5. Contributor Expectations
Any contribution that improves algorithm efficiency or add new visualization types are welcomed!

* **Code Style:** Keep UI logic in `MainWindow` and visualization logic within the specific visualizer classes (`TreeVisualizer`, `GraphVisualizer`, etc.).
* **Animation System:** New algorithms should use the `stepsList` pattern with `std::tuple` to ensure smooth, non-blocking animations.
* **Branching:** Please create a feature branch (`git checkout -b feature/NewAlgo`) before submitting a Pull Request.
* **Verification:** Ensure all traversals are printed to the terminal using `qDebug()` or `QTextStream(stdout)`.

---

**Author:** [Shahrin Mithila](https://github.com/AntaraAn)  
**License:** MIT License
