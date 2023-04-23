
curl -X GET \
    -H "Authorization: Bearer $(gcloud auth print-access-token)" \
    "https://cloudresourcemanager.googleapis.com/v3/projects/vocabulary"
