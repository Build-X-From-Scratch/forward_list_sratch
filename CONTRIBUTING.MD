# Guide For Contribute

## step 1
fork this repo
```bash
git clone https://github.com/Build-X-From-Scratch/forward_list_sratch.git"
cd forward_list_sratch
```
if you use ssh
```bash
git@github.com:Build-X-From-Scratch/forward_list_sratch.git
cd forward_list_sratch
```
and if you use GitHub CLI
```bash
gh repo clone Build-X-From-Scratch/forward_list_sratch
cd forward_list_sratch
```
## Step 2
create branch for your task
```bash
git checkout -b your_branch
```
if there is changes on upstream 
```bash
git remote add upstream https://github.com/Build-X-From-Scratch/forward_list_sratch.git
git fetch upstream
git merge upstream/main
```
## Compile & Build
this project need linking implementation.cpp and header
but for keep it simple developing,i create shell scripting
- for compile 
```bash
./compile.sh
```
- for build unit testing
```bash
./build_testing.sh
```
# Step 3
create pull request
```bash
git commit -am "your msg"
git push origin your_branch
```
# step 4 
Keep Smiling Stupid


