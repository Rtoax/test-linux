=====
Regex
=====

- `.`: matches any single character;
- `.*`: matches any character of any length;
- `\?`: matches the preceding character 0 or 1 time;
- `+`: matches the preceding character at least once, or multiple times consecutively;
- `{n}`: matches the preceding character when it appears consecutively exactly n times;
- `{x,y}`: matches the preceding character when it appears consecutively at least x times and at most y times; it will be matched as long as it is between x and y;
- `{,n}`: matches the preceding character when it appears consecutively at most n times and at least 0 times;
- `{n,}`: matches the preceding character only when it appears consecutively at least n times;
