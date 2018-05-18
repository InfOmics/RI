# RI
RI is a general purpose algorithm for one-to-one exact subgraph isomorphism problem maintaining topological constraints. 

<hr />

### Description
***RI*** is a general purpose algorithm for one-to-one exact subgraph isomorphism problem maintaining topological constraints. It is both a C++ library and a standalone tool, providing developing API and a command line interface, with no dependencies out of standard GNU C++ library. RI works on Unix and Mac OS X systems with G++ installed, and it can be compiled under Windows using Gygwin. Working graphs may be directed, undirected, multigraphs with optional attributes both on nodes and edges. Customizable features allow user-defined behaviors for attribute comparisons and the algorithm's flow.


***RI*** aims to provide a better search strategy for the common used backtracking approach to the subgraph isomorphism problem. It can be integrated with additional preprocessing steps or it can be used for the verification of candidate structures coming from data mining, data indexing or other filtering techniques. RI is able to find graphs isomorphisms, subgraph isomorphisms and induced subgraph isomorphisms. It is distributed in several versions divide chiefly in two groups respectively for static or dynamically changing attributes. All proposed versions are developed taking into account trade-offs between time and memory requirements. Optional behaviors such as stop at first encountered match, processing of result matches, type of isomorphism and additional features may be enabled thanks to high modularity and library's API.

The ***RI*** project also aims to provide a comparison of existing exact subgraph matching algorithms on synthetic and real life graphs. An initial collection of datasets is proposed, it includes synthetic and biological graphs but further types of data regarding other research areas (i.e. engineering, computer vision, etc...) are coming. A list of proposed application is also given.

Please send us an email to get software sources or datasets (see Contacts).

<hr />

### License
RI is distributed under the MIT license. This means that it is free for both academic and commercial use. Note however that some third party components in RI require that you reference certain works in scientific publications.
You are free to link or use RI inside source code of your own program. If do so, please reference (cite) RI and this website. We appreciate bug fixes and would be happy to collaborate for improvements. 

<hr />

### Citation
     """Bonnici, V., Giugno, R., Pulvirenti, A., Shasha, D., & Ferro, A. (2013).
     A subgraph isomorphism algorithm and its application to biochemical data. 
     BMC bioinformatics, 14(7), S13.

<hr />

### References
 if you have used any of the RI project software, please cite the following paper:
 
Vincenzo Bonnici, Rosalba Giugno, Alfredo Pulvirenti, Dennis Shasha and Alfredo Ferro. A subgraph isomorphism algorithm and its application to biochemical data. BMC Bioinformatics 2013, 14(Suppl 7):S13 doi:10.1186/1471-2105-14-S7-S13.
