## Directory structure:
 - Please move code to (a subdirectory) of src, if not already done.
 - Please create a make target `all` in each subdirectory of `src`.
   It can be recursive, e.g. MAS/Makefile calls `make` in some subdirectory.
 - Always use option `-Wall` to g++: example warning `c++ control reaches end of non-void function
 
 ```C++
Color ColorBasedOnMapping(string kmer){
      if (kmerSize==3) {
           ...
           return ...
      }
      // return missing in this case
}
 ```
 - Each subfolder can have its own `.gitignore`, e.g. to exclude the binaries therein
   from the repo.

## Commenting
 - Please use [doxygen-style](https://github.com/mslehre/MAS/wiki/Documentation-with-doxygen) comments from now on.
 - We will setup the automatic execution of doxygen soon.

## Versions
 - Please do not maintain several versions of the code in different directories.
   => Others do not know which version to work on or with.
 - Please send me a pull request to delete old versions of your code if they are now in
   origin/master.
 - Git can deal with moved source files.
 - Do not continue to work on feature branch after pull request (conflicts between requested changes and continued work).
   Rather create a new branch for continuing work, this can branch off the last version with

```git branch feature/newbranchname feature/oldbranchname```

## Refactor
 Do not reinvent the wheel, e.g. reuse a suitable existing list of well-distinguishable RGB values
 Do not use DOS linebreaks.
 
### Color palette (Lucas)
1) The one-to-one correspondence between (DNA) letter and number (e.g. of type `char`) should be specified only once.

```C++
   int charRead(char character){
       if (character=='A')
           return 0;
       else if(character == 'C')
           return 1;
       else if(character == 'T')
           return 2;
       else if(character == 'G')
           return 3;
    }
```

   and

```C++
    string alphabet = "ACTG";
```

2) Color palette should not require to include a graph => modularize better

3) Color map: assignment k-mer <-> color need not be stable across different problem instances.

4) `kmercolor.cc` references `Graph::getSimpleKOfKmer()` that does not exist.

### Graph construction (Sebastian)
1) Lines too long. GitHub needs a horizontal scrollbar to show the code.
2) Tabs instead of space, inconsistent alignment of comments
```C++
std::vector<std::array<int,3>> listOfEdges;					// vector of edges (as array with size 3)
std::vector<std::string> stringListSequence;				// vector of strings for the sequences
std::vector<int> numberOfKmer;								// vector amount of k-mer
```
3) Graph does not need to know _k_.

4) `Edges` should probably be pairs of `Nodes`, rather than `array<int,3>`.
   This abstraction allows e.g. to consider edges that are not between neighboring sequences.

5) The sequence itself need not be displayed. It is irrelevant for the game or RL problem and probably clutters the image.
 `std::vector<std::string> stringListSequence;`


### Visualization (Moritz)

1) Lines too long. Tabs instead of space. Comment style.

2) Variable name: `kMer` is expected to be a string of lenght k, not an int.

3) What is wrong here?
```C++
const vector<int>& Graph::getNumberOfKmer(){
	int numStrings=stringListSequence.size();					// amount of sequences
	for(int i=0; i<numStrings; i++){								// for-loop to get number of k-mer
		numberOfKmer.push_back(splitString.at(i).size());
        }
	return numberOfKmer;
}
```

4) `splitString` does not seem to be initialized before `splitString.at(i).push_back()` is called

5) _k_-mers can have less than k characters at sequence end - don't allow that (statistical significance)

6) Don't make the secret, undocumented assumption that _k_-mers cannot overlap.
```C++
for(int j=0; j<stringListSequence.at(i).length(); j=j+kMer){
```
Rather, introduce a variable `unsigned shift`

```
<-------- k ------->
--------------------
<-shift->
        --------------------
        <-shift->
                --------------------
```
and default it to _k_.

### State + Actions (Maurice)
1) Avoid multiple vectors that are supposed to be of the same length(?).
```C++
  std::vector <std::array<int,3>> edges; 
  std::vector <bool> consistentSubset; //shows whether edge is selected in current subset (true=selected)
  std::vector <bool> selectable; //shows whether edge is selectable in the current subset (true=selectable)
```
Rather, define a new tuple, class or struct and use a single vector, e.g.
`EdgeChoice (Edge e, bool chosen, bool selectable)`

2) Unintuitive name: `void state::possibleActions(void)`

3) Do not use `l` as variable name.

4) Algorithm in `state::possibleActions` needs documentation.
   Also the consistency check of a pair of edges should be moved
   to a separate function.