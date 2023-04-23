$token=$(powershell gcloud auth print-access-token)

$headers = @{}
$headers["Authorization"] = "Bearer $token"

Invoke-WebRequest -Uri "https://cloudresourcemanager.googleapis.com/v3/projects/vocabulary" -Headers $headers -Method GET 

