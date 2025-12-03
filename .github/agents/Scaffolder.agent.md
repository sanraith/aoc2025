---
description: Agent for scaffolding files for a new Advent of Code puzzle day.
tools: [ insert_edit_into_file, replace_string_in_file, create_file, run_in_terminal, get_terminal_output, get_errors, show_content, open_file, list_dir, read_file, file_search, grep_search, run_subagent ]
---

# 'Scaffold' Instructions

When asked to scaffold for a given day or just 'scaffold', your job is to perform the following operations on this
repository in order.
Should any of these steps fail, you must stop completely and report the error.
While working, you must only report the current active high level step referring to it using the exact name as defined
below.
BE VERY CONCISE. Do not explain details.
YOU MUST NOT perform any additional steps, only the ones defined below.
YOU MUST NOT try to build the project after you are done.
YOU MUST NOT formulate any kind of action plan.
YOU MUST NOT run any command-line command unless specified in a step below.
YOU MUST NOT read any other files than the ones specified in the steps below.
If you cannot find the exact file specified, you must stop and report an error.
YOU MUST NOT offer any follow-up steps.
YOU MUST NOT check for any build errors.

During the scaffolding process, you have to find and replace the following placeholders.
You will have to replace them both in the generated file name and the generated file content.

- `__DAY__`: The day number the scaffolding is requested for. Use the current day of the month if not provided.
  E.g.: `5` or `12`.
- `__DAY_PADDED__`: Same as `__DAY__`, but padded to two digits. E.g.: `05` or `12`.
- `__YEAR__`: The year number the scaffolding is requested for. Use the current year if not provided.
  E.g.: `2023` or `2025`.
- `__PUZZLE_URL__`: The URL of the puzzle description for the given day and year:
  `https://adventofcode.com/__YEAR__/day/__DAY__`
- `__TITLE__`: The title of the puzzle. Use the extracted value from step 3.
- `__EXAMPLE_INPUT__`: The example input provided in the puzzle description. Use the extracted value from step 3.
- `__EXAMPLE_RESULT_PART1__`: The example result for part 1 provided in the puzzle description. Use the extracted value
  from step 3.

Before you start, you should respond with "Following custom scaffolding instructions for __YEAR__/__DAY_PADDED__...".

## Step 1: Opening the puzzle description

Run the following command in the terminal to open the puzzle description in the default web browser:

- If on Windows: `Start-Process 'https://adventofcode.com/__YEAR__/day/__DAY__'`
- If on Linux or Mac: `open 'https://adventofcode.com/__YEAR__/day/__DAY__'`

## Step 2: Running scaffolder to download input and puzzle description

Run the following command in the terminal to invoke the scaffolder script to download input and puzzle description:

- If on Windows: `.\cmake-build-debug-win\scaffold.exe -y __YEAR__ -d __DAY__`
- If on Linux or Mac: `./cmake-build-debug-linux/scaffold -y __YEAR__ -d __DAY__`

## Step 3: Loading template data from the puzzle description

Read the template description of the puzzle for the given day from `.cache/__YEAR__day__DAY_PADDED___puzzle.txt`.
Extract the following data from the puzzle description:

- The title of the puzzle for placeholder into `__TITLE__`.
  The title is usually found at the top of the description surrounded by `<h2>` tags.
  For example, from `<h2>--- Day 1: Historian Hysteria ---</h2>` you would extract `Historian Hysteria`.
- The example input for placeholder into `__EXAMPLE_INPUT__`. The example input is surrounded by `<pre><code>` tags.
  For example, from `<pre><code>example input</code></pre>` you would extract `example input`.
- The example result for part 1 for placeholder into `__EXAMPLE_RESULT_PART1__`. The example result is usually
  surrounded by `<code><em>` tags.
  For example, from `<code><em>42</em></code>` you would extract `42`.

Try to find multiple complete examples (ones that do not need alteration of the puzzle rules to apply),
and take note of their `__EXAMPLE_INPUT__` - `__EXAMPLE_RESULT_PART1__` pairs.

## Step 4: Creating a new solution source file

Using template `src/templates/Day__DAY_PADDED__.h`,
create a new source file for the given day at `src/solutions/`.
DO NOT make any alterations to the template other than replacing the placeholders defined above.

## Step 5: Updating the solution index

Update the contents of `src/solutions/index.cpp` to include a reference to the newly created file.
Make sure to add both an appropriate include statement and an entry in `solutions`.
For example, the Day 1 map entry in `solutions` must look like:

```cpp
{{2025, 1}, [] { return std::make_unique<year2025::Day01>(); }},
```

## Step 6: Creating a new test source file

Using `src/templates/Day__DAY_PADDED__Test.cpp` as the template,
create a new test source file for the given day at `tests/solutions/`.
Repeat the example `TEST_CASE() {...}` section for every complete `__EXAMPLE_INPUT__` - `__EXAMPLE_RESULT_PART1__` pairs,
naming them "... input 1", "... input 2" and so on.
DO NOT make any alterations to the template other than what is defined above.

## Step 7: Updating CMakeLists.txt

Update `CMakeLists.txt` to add the new solution source file to library `aoc2025lib`.  
Update `tests/CMakeLists.txt` to add the new test source file to executable `tests`.

## Step 8: Reporting completion

As a final step, respond with the text "Scaffolding for __YEAR__/__DAY_PADDED__ completed successfully.".