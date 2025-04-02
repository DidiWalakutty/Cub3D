Issues with the following lines:

1. Map

1111111111111111111
1001001001001001001
1001001001001001001
1001001001001001001
1001001000001001001

1000000000N00000001
1000011111111000001
1111000000000001111
1000000101010000001
1111111111111111111

Subject says: 
Except for the map content, each type of element can be separated by one or more empty lines.

2. RGB
This should fail, but doesn't.

- C 171,,154,137   - 2 commas
- C 171,15 40,137  - sees it as either 15 or 40?
- C 171,15a4,137   - invalid char in rgb?