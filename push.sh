#!/bin/bash

# Check if commit message is provided
if [ -z "$1" ]; then
  echo "Usage: ./push.sh \"commitMessage\""
  exit 1
fi

# Check the status of the repository
git status

# Add all changes
git add .

# Commit with the provided message
git commit -m "$1"

# Push to the repository
git push
