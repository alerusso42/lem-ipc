# NOTE – Usage, Credits, Details

# FIXME - valgrind leak with current conf, not accepts hash == 0

# SECTION - What This Database Does
This database lets you quickly find and retrieve data from a set of text put in data/ directory.
It uses a hash-based lookup so that, given a key (e.g., "DATA1"), you immediately get the associated value (e.g., "apple").

Example file format (key–value pairs):
DATA1=apple
DATA2=red
DATA3=tasty,good
...
If you call daft_get("DATA1") you get back "apple".

You can format file in multiple field key-value, too.
Example:
FRUIT1|
Type:apple
Color:green
Size:150 ml
Weight:150 g
FRUIT2|
Type:banana
Color:yellow
Size:110 ml
Weight:90 g
...

If you call daft_get("FRUIT1") you get back ["apple", "green", "150 ml", "150 g"].

Internally, you can choose how values are split and stored (read "How to Format Your Data Files").

# SECTION - How to Add or Remove Files

1) Go into the data/ directory.

2) Add or remove files anywhere under data/.
Files can be nested in subfolders.
Ignored file types: .sh, .c, .h, .o, .out, Makefile, or .md.

3) From the project root, run:
chmod +x update.sh
./update.sh
This scans data/ and updates SETTINGS.md.

4) Open SETTINGS.md and adjust any per‐file or global flags.

5) Run:
./update.sh
again so the script rebuilds hashes with your new settings.

# SECTION - How to Format Your Data Files

Each data file has a flexible format. You can define how to parse it by specifying per-file rules in SETTINGS.md.
These rules declare:
- which lines to extract,
- how to split the fields,
- how the returned data should be structured.

⚠️Before modifying SETTINGS.md, make sure to run update.sh.⚠️
Each rule follows this pattern :
filename->[field separator][multiple lines?][split_values?][key_value_separator][value_separator]
Example:
data/pokedex/pokedex.txt->]yy=,

| Symbol | Position | Description                                                                                               |
| ------ | -------- | --------------------------------------------------------------------------------------------------------- |
| `]`    | 1st      | **field separator** – only lines that begin with this character are considered (e.g., `]BULBASAUR`) 		|
| `y/n`  | 2nd      | **multiple lines** – if `y`, the data is returned as a matrix of strings (i.e., a list of fields)       	|
| `y/n`  | 3rd      | **split values** – if `y`, each field's value (e.g., `GRASS,POISON`) is further split into an array 		|
| `=`    | 4th      | **key-value separator** – character used to separate keys and values (e.g., `Name=Bulbasaur`)             |
| `,`    | 5th      | **value separator** – used to split lists of values within a field (e.g., `Types=GRASS,POISON`)           |

Of course, symbol can be changed.

Example. File is:
# ------------------------------------- # 
	BULBASAUR]							|
	Id=0								|
	Name=Bulbasaur						|
	Types=GRASS,POISON					|
	BaseStats=45,49,49,45,65,65			|
	...									|
	IVYSAUR]							|
	Id=1								|
	Name=Ivysaur						|
	Types=GRASS,POISON					|
	BaseStats=60,62,63,60,80,80			|
	...									|
# ------------------------------------- #

# Simple key-value
SETTINGS: data/pokedex/pokedex.txt->=nn=,
# daft_get("Name")
	"Bulbasaur"

# Matrix of values
SETTINGS: data/pokedex/pokedex.txt->=ny=,
# daft_get("Types")
	["GRASS","POISON"],

# Matrix of keys
SETTINGS: data/pokedex/pokedex.txt->]yn=,
# daft_get("BULBASAUR")
	["0", "Bulbasaur", "GRASS, POISON", "45,49,49,45,65,65"]

# 3D matrix
SETTINGS: data/pokedex/pokedex.txt->]yy=,
# daft_get("BULBASAUR")
	["0"], 
	["Bulbasaur"], 
	["GRASS","POISON"], 
	["45","49","49","45","65","65"]


All flags are optional.
Default flags are set in SETTINGS.md.

CREATOR & LICENSE
Database tool by Alessandro Russo (GitHub: alerusso42).
Feel free to use, modify, and redistribute. 
⚠️Please credit the author when sharing or publishing.⚠️