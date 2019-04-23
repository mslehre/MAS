<p style='text-align: right;'><small>Mario Stanke, April 22nd, 2019</small></p>

## Coding Issues / Refactoring
 - Graph
   - `G=(V, E)` set of nodes and edges
   - What is the node set?
 - no trailing white spaces
 - strategic decision: we will require compiler that allows __`--std=c++11`__ (requires at least GCC version 4.8.1)
  That means the following is possible/available:
   - auto types
   - `vector<string> vs={ "first", "second", "third"};`
   - "new" container classes `unordered_map`, `ordered_map`, e.g.
   `  unordered_map<string,string> fruitcol ( {{"apple", "red"},{"lemon", "yellow"}} );`
   - `nullptr` for a NULL pointer
   - thread library: `#include <thread>`
   - don't call a program "Program" or "main"

## Management
 - general __communication__: please summarize your changes in response to a review.
   In particular, write and justify if you have not realized a request.
 - importance of software engineering skills for job outlook, 
 [Absolventenumfrage](https://math-inf.uni-greifswald.de/studium-und-lehre/studiengaenge/biomathematik/absolventenumfrage/):   "geben ca. 80% der Absolventen an, dass sie während ihrer Arbeit hauptsächlich mit Programmieren beschäftigt sind"

## Continuous Integration
 - TRAVIS CI configured (demo), see `.travis.yml`
 - Every pull request is checked. Green circle on GitHub if no error.
 - automatic documentation of `master` branch using gp-pages: https://mslehre.github.io/MAS
 