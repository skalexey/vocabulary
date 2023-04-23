#!/bin/bash
THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
token=$(powershell gcloud auth print-access-token)
echo "token: '$token'"
curl -X GET \
    -H "Authorization: Bearer $token" \
    "https://cloudresourcemanager.googleapis.com/v3/projects/vocabulary-382120"
