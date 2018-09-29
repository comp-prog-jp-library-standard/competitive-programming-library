# This script bundles all *.cpp files in ./library/cpp/src into a single file.
# It generates JSON and puts into ./docs/lib.json file.
# It requires Python 3.x (not 2.x)

import glob
import json

def loadFile(fileName):
  with open(fileName) as file:
    return { 'sourceFile': fileName, 'source': file.read() }

# Enumerate files. This includes files in subdirectories.
fileNames = glob.glob('./library/cpp/src/**.cpp', recursive=True)

# Load file contents.
fileContents = list(map(loadFile, fileNames))

# Write as a JSON
with open('docs/lib.json', mode='w') as file:
  file.write(json.dumps(fileContents))
