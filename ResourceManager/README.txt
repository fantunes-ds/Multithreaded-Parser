How the Multithreaded parser works :

1) Create a Gameobject in App.cpp
2) Add a ModelComponent to the newly created gameobject. It requires the path to a mesh.
3) Model constructor calls LoadModel with the path as parameter.
4) LoadModel first searches if the mesh has already been created, if true, it assigns the given mesh
	If not, it will load it in the ressourceManager through AddMesh() with path as parameter
	NOTE : AddMesh is threaded, and will parse the object and add it to a vector of Mesh*
5) The parser retrieves all raw data (directly from the file without edit) and separates them into
	appropriate containers. Then it rearranges indices so that the output vertices are already
in the right order and only need to be drawn, thus replacing the EBO.
NOTE : The LoadFaces() function works for both Triangles and Quads, but other geometry will not be loaded.
6) Once data has been parsed, it is added in an unordered map. A std::pair defines the loading status
of the corresponding mesh.
7) Back to Model.cpp, we generate buffers for the newly added mesh in the ResourceManager,
8) If the mesh is loaded, we assign it to our mesh, it points to the data in ResourceManager 
	(FlyWeight pattern)
9) We load the shader, and we're good to go. 
10) Enjoy
