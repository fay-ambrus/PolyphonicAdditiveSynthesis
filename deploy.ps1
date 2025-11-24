# CONFIGURATION
$ServerUser = "cloud"                               # SSH username
$ServerHost = "vm.smallville.cloud.bme.hu"          # server address
$ServerPort = "6906"                                # SSH port
$ServerPath = "/var/www/html/moodle"                # path to Moodle on server
$CommitMessage = if ($args.Length -gt 0) { $args[0] } else { "Auto commit from script $(Get-Date)" }

# Commit and push locally
Write-Host "Adding changes..."
git add .

# Only commit if there are changes
$changes = git status --porcelain
if ($changes) {
    Write-Host "Committing changes: $CommitMessage"
    git commit -m "$CommitMessage"
} else {
    Write-Host "No changes to commit."
}

Write-Host "Pushing to $RemoteName/$LocalBranch..."
git push $RemoteName $LocalBranch

# SSH into server and pull
Write-Host "Connecting to server and pulling changes..."
ssh $ServerUser@$ServerHost -p $ServerPort "cd $ServerPath && sudo git fetch --all && sudo git reset --hard $RemoteName/$LocalBranch && sudo php admin/cli/purge_caches.php"

Write-Host "Done!"
