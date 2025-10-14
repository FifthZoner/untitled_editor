from datetime import datetime
from os import listdir, path

current_version  = "0.0.1 pre 0"
cache_file_extension = ".cache"

# this script simply takes the cache file and adds a number to it while also generating version header file for ???
# I admit I copied it from Dodo Lang, but I still wrote it so who cares

# checking git dir
if not path.exists("../.git") or not path.isdir("../.git") or not path.exists("../.git/HEAD") or not path.isfile("../.git/HEAD"):
    print("Error: Expected a valid .git directory in parent directory!")
    quit(-1)

# finding the current branch
branch = ""
with open("../.git/HEAD", "r") as f: content = f.read().splitlines()

for line in content:
    if line[0:4] == "ref:":
        branch = line.partition("refs/heads/")[2]

if branch == "":
    print("Error: Could not find current branch!")
    quit(-1)

print("Current branch: " + branch)

print("Looking for branch cache files...")

total_build = 0
branch_build = 0
found_current = False
files = listdir(".")
for file in files:
    if file.endswith(cache_file_extension):

        if file.startswith("."):
            print("Error: Invalid file name: \"" + file + "\"!")
            quit(-1)

        print("Found file: " + file)
        data = open(file, "r")
        value = data.readline().replace("\n", "")
        if not value.isdigit():
            print("Warning: Expected cache file content to be a number!")
            continue
        data.close()

        value = int(value)
        file_branch = file.split(".")[0]

        if (file_branch == branch):
            print("Found cached builds number: " + value.__str__())
            found_current = True

            print("Saving incremented value...")
            value += 1
            branch_build = value

            cache = open(file, "w")
            cache.write(value.__str__())
            cache.close()
            print("Saved!")
        else:
            print("Loaded build value: " + value.__str__() + ", for branch: " + file_branch)

        total_build += value

if not found_current:
    print("Cached value for current branch not found, creating a new file...")
    total_build += 1
    branch_build = 1

    cache = open(branch + cache_file_extension, "w")
    cache.write("1")
    cache.close()
    print("Saved value for current branch!")

print("Total build number is: " + total_build.__str__())

# and finally generating the header
print("Generating incremented header file...")
header = open("../src/generated/version.hpp", "w")
header.writelines([
    "// This file was generated automatically WILL be overwritten on compilation\n"
    "// The total build number may be inaccurate \n"
    "#ifndef VERSION_HPP\n"
    "#define VERSION_HPP\n"
    "\n"
    "inline auto version = \"" + current_version + "\";\n"
    "inline auto branch = \"" + branch + "\";\n"
    "inline auto branchBuild = \"" + branch_build.__str__() + "\";\n"
    "inline auto totalBuild = \"" + total_build.__str__() + "\";\n"
    "inline auto buildTime = \"" + datetime.today().strftime('%Y-%m-%d %H:%M:%S') + "\";\n"
    "\n"
    "#endif"
])
header.close()

print("Done generating, compilation can proceed!")