import os
import re

def find_cpp_classes(directory):
    class_regex = re.compile(r'\bclass\b\s+(\w+)')
    classes = set()

    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith('.cpp') or file.endswith('.h'):
                with open(os.path.join(root, file), 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    matches = class_regex.findall(content)
                    classes.update(matches)

    return classes

# Specify the directory of your C++ project
project_directory = './'

# Find and print all class names
cpp_classes = find_cpp_classes(project_directory)
for cpp_class in cpp_classes:
    print(cpp_class)
