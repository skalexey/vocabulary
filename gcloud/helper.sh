#!/bin/bash

gproject_id="vocabulary-382120"

function get_access_token() {
    powershell gcloud auth $1 print-access-token
}

function gcurl() {
    curl -H "Authorization: Bearer $(get_access_token $2)" -H "Content-Type: application/json" $1
}

function auth() {
    gcurl "https://cloudresourcemanager.googleapis.com/v3/projects/$gproject_id" $1
}

function keys() {
    gcurl "https://apikeys.googleapis.com/v2/projects/$gproject_id/locations/global/keys"
}

$1 ${@:2}