#!/usr/bin/env bash
# =============================================================================
# update_imanim.sh
# =============================================================================
# One-click script to fetch the **latest** ImAnim library from GitHub
# and place im_anim.h / im_anim.cpp / LICENSE into libs/ImAnim/
#
# Run from the root of your ofxImAnim addon:
#     ./update_imanim.sh
# =============================================================================

set -euo pipefail

# ----------------------------- CONFIG -----------------------------
REPO="soufianekhiat/ImAnim"
BRANCH="main"                    # Default branch (confirmed — not master)
LIB_DIR="libs/ImAnim"

FILES=(
    "im_anim.h"
    "im_anim.cpp"
    "LICENSE"
)

BASE_URL="https://raw.githubusercontent.com/${REPO}/${BRANCH}"

# ------------------------------------------------------------------

echo "🚀 Updating ofxImAnim → ImAnim library (branch: ${BRANCH})"
echo "   Target folder: ${LIB_DIR}/"

# Create folder if it doesn't exist
mkdir -p "${LIB_DIR}"

# Download each file
for file in "${FILES[@]}"; do
    echo "   ↓ Fetching ${file} ..."
    curl -L --silent --fail --output "${LIB_DIR}/${file}" "${BASE_URL}/${file}"

    # Quick sanity check
    if [[ -s "${LIB_DIR}/${file}" ]]; then
        echo "${file} downloaded ($(wc -c < "${LIB_DIR}/${file}") bytes)"
    else
        echo "Failed to download ${file}"
        exit 1
    fi
done

echo ""
echo "Done! ImAnim is now up-to-date in ${LIB_DIR}/"
echo "   Files updated:"
echo "     • ${LIB_DIR}/im_anim.h"
echo "     • ${LIB_DIR}/im_anim.cpp"
echo "     • ${LIB_DIR}/LICENSE"
echo ""
