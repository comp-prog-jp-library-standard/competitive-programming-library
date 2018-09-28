# If not master branch, skip jobs.
if [ "${CIRCLE_BRANCH}" != "master" ]; then
  echo "Current branch ${CIRCLE_BRANCH} is not master. Aborted."
  exit 0
fi

# Set commiter for auto generated files
git config user.name "vvataarne"
git config user.email "is0399ii@ed.ritsumei.ac.jp"

# Generate documents
python ./bin/generate-docs.py

# Push changes to GitHub Pages
./bin/push-docs.sh
