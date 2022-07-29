
# Adding Edge to Minimum Spanning Tree

This code updates a given **MST** after adding an edge to it.
## Problem
Minimum Spanning tree of a graph consisting of N 
nodes have been created using **Kruskal** algorithm.
The edge weights found in the 
graph's MST and the nodes between which these
edges exist are provided as input data, with 
the edge weights listed in ascending order.   

[![Sample-MST.jpg](https://i.postimg.cc/3x55gVtf/Sample-MST.jpg)](https://postimg.cc/mtw54Xf7)

A new edge is created in the graph between two nodes. 
The value of this edge and the nodes it connects are provided
by the **user** as input data. We have to create the algorithm that 
updates the MST based on this new edge information.
## Solution
If we add an Edge from **U** to **V** with the weight equal to **W**,
there will be 4 cases:

1. There is an Edge from U to V , and the new 
Edge is smaller. Thus we replace the current 
edge with the new one (with the shorter one).
[![1.jpg](https://i.postimg.cc/yxsQXLnM/1.jpg)](https://postimg.cc/JDY5Rcfx)

2. There is an Edge from U to V , and the new 
Edge is larger. So the MST remains unchanged.
[![2.jpg](https://i.postimg.cc/7ZdKQHmM/2.jpg)](https://postimg.cc/NK88Kch5)

3. There is no edge between U and V. When we 
add the new edge, we will create a cycle between 
U and V. As a result, we must find the unique path 
from U to V and update the MST.
If the new Edge is shorter than the largest Edge in 
the path , the new Edge is added to the MST 
and the largest Edge is removed.     
[![311-Capture.jpg](https://i.postimg.cc/FRgGRjmD/311-Capture.jpg)](https://postimg.cc/XGq91BrC)
The unique path will be like:
[![312.jpg](https://i.postimg.cc/cCFm70v3/312.jpg)](https://postimg.cc/kRtKqrFM)

Otherwise, MST remains unchanged.
[![321.jpg](https://i.postimg.cc/hPGMDzY1/321.jpg)](https://postimg.cc/QVRcSthF)

4. The input nodes (V or U or both) are not in the MST, so MST 
remains unchanged.
[![4.jpg](https://i.postimg.cc/sgQcSFsB/4.jpg)](https://postimg.cc/TKxgM4yG)

## Requirements
- Any Text Editor (VSCode, XCode, DevC++)
- GCC Compiler   

## How to Run
Run the commands below on the Path where the File is saved.

 on Linux: 
```bash
gcc AddEdge_MST.c -o AddEdge_MST.exe
./AddEdge_MST
```
on Windows:

```bash
gcc AddEdge_MST.c -o AddEdge_MST.exe
AddEdge_MST.exe
```
on Mac:

```bash
gcc -Wall -o AddEdge_MST AddEdge_MST.c
./AddEdge_MST
```

## Contact 
Don't hesitate to ask your questions via E-mail at
amirkia.rafiei@gmail.com
## Authors

- [@Amirkia1998](https://github.com/Amirkia1998)


## Solution
If we add an Edge from **U** to **V** with the weight equal to **W**,
there will be 4 cases:

1. There is an Edge from U to V , and the new 
Edge is smaller. Thus we replace the current 
edge with the new one (with the shorter one).
[![1.jpg](https://i.postimg.cc/yxsQXLnM/1.jpg)](https://postimg.cc/JDY5Rcfx)

2. There is an Edge from U to V , and the new 
Edge is larger. So the MST remains unchanged.
[![2.jpg](https://i.postimg.cc/7ZdKQHmM/2.jpg)](https://postimg.cc/NK88Kch5)

3. There is no edge between U and V. When we 
add the new edge, we will create a cycle between 
U and V. As a result, we must find the unique path 
from U to V and update the MST.
If the new Edge is shorter than the largest Edge in 
the path , the new Edge is added to the MST 
and the largest Edge is removed.     
[![311-Capture.jpg](https://i.postimg.cc/FRgGRjmD/311-Capture.jpg)](https://postimg.cc/XGq91BrC)
The unique path will be like:
[![312.jpg](https://i.postimg.cc/cCFm70v3/312.jpg)](https://postimg.cc/kRtKqrFM)

Otherwise, MST remains unchanged.
[![321.jpg](https://i.postimg.cc/hPGMDzY1/321.jpg)](https://postimg.cc/QVRcSthF)

4. The input nodes (V or U or both) are not in the MST, so MST 
remains unchanged.
[![4.jpg](https://i.postimg.cc/sgQcSFsB/4.jpg)](https://postimg.cc/TKxgM4yG)
