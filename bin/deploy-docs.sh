set -eu

# Set commiter for auto generated files
git config user.name "koba-e964"
git config user.email "3303362+koba-e964@users.noreply.github.com"

# Generate documents
python ./bin/generate-docs.py

# Get short hash of HEAD (the target commit)
REVISION=$(git rev-parse --short HEAD)

# Commit changes
git add docs
git commit -m "Generate pages for ${REVISION} [ci skip]"
echo "Commited"

# Push docs to gh-pages branch
branch_name=$(git subtree split --prefix docs master)
if [ -n ${branch_name} ]
then
    git push origin -f ${branch_name}:gh-pages
fi
echo "Pushed"
