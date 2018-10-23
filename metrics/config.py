#****findIncludes.py****
#pairs alternative extension with main extension (for example, a c++ program can also end in .cc)
substituteDict = {"cc":"cpp", "hh":"hpp"}
#pairs language with id for csv file (used to generate DOT file for graph)
idDict = {"c":1, "cpp":1, "h":2, "hpp":2, "py":3, "js":4}
#pairs language with appropriate island grammar
grammarDict = {"c":["cinclude"], "cpp":["cinclude"], "h":["cinclude"], "hpp":["cinclude"], "py":["pyimport"], "js":["jsrequire", "jsimport"]}
#used to hold statistics for each language
stats = {"c":[], "cpp":[], "h":[], "hpp":[], "py":[], "js":[]}
#the languages to analyze
progtypes = ['c', 'cpp', 'h', 'hpp', 'py', 'js']
#progtypes = ['js']


#****generateIncludeDOT.py****
# pairs language with corresponding id
typeDict = {'c':'1', 'cpp':'1', 'h': '2', 'hpp':'2', 'py':'3', 'js':'4'}
# pairs id with corresponding node shape
shapeDict = {'1':'oval', '2':'diamond', '3':'rectangle', '4':'hexagon'}
# pairs id with corresponding include id (for example, a c/c++ program can only include an h/hpp program, python can only include python...)
includeTypeDict = {'1':'2', '2':'2', '3':'3', '4':'4'}