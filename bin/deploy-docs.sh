# Set commiter for auto generated files
git config user.name "vvataarne"
git config user.email "is0399ii@ed.ritsumei.ac.jp"

# Generate documents
python ./bin/generate-docs.py

# Get short hash of HEAD (the target commit)
REVISION=$(git rev-parse --short HEAD)

# Commit changes
git add docs
git commit -m "Generate pages for ${REVISION} [ci skip]"
echo "Commited"

# Push docs to gh-pages branch
git push origin -f $(git subtree split --prefix docs master):gh-pages
echo "Pushed"
