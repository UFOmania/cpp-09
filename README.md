# cpp-09


# Bitcoin Exchange

we have a dataset containes the bitcoin prices at some data time.

```csv
date,exchange_rate
2009-01-02,0
2009-01-05,12
2009-01-08,448
2009-01-11,77
```

we will take a **input file as an argumenst**.
the task is check for the **price** of the **amount** of bitcoin at that **time** stamp.

```csv
    date | value
    2011-01-03 | 3
    2011-01-03 | 2
    2011-01-03 | 1
    2011-01-03 | 1.2
    2011-01-09 | 1
    2012-01-11 | -1
    2001-42-42
    2012-01-11 | 1
    2012-01-11 | 2147483648
```

## example

```ini
    $> ./btc input.txt
    2011-01-03 => 3 = 0.9
    2011-01-03 => 2 = 0.6
    2011-01-03 => 1 = 0.3
    2011-01-03 => 1.2 = 0.36
    2011-01-09 => 1 = 0.32
    Error: not a positive number.
    Error: bad input => 2001-42-42
    2012-01-11 => 1 = 7.1
    Error: too large a number.
```


# mental aproach:

## 1- load data.csv

- open *data.csv* with **ifstream**
- iterate with each line 
    - check is the date and price is valid,
    - normalize the date to follow this 'YYYY-MM-DD'.
    - save date as **key** and price as **value**.
    - in case of an error 'bad input, can't get line, bad filename , ...' throw exception and exit.
    ```ini
    key   [2011-02-03]
    value [54.26]
    ```

## 2- execute input.csv

- open *input.csv* with **ifstream**
- iterate with each line
    - in this case of a bad input we skip this line and prmpte a valid error msg.
    - **validate the time**
        - check if that time exist
            - eg: *2000-02-31 is not valid*
        -normalize date to folloe YYYY-MM-DD
    - **validate amount**
        - is it positive and between 0 and 1000
    
    - **search for time**
        - search for the target date in the map
        - if not found look for the date befor target using *lowe_bound() - 1*;
        - print the result;
    
# RPN: Reverse Polish notation

- calculate the result RPN matimatical formula.
```ini
    $> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
    42
    $> ./RPN "7 7 * 7 -"
    42
    $> ./RPN "1 2 * 2 / 2 * 2 4 - +"
    0
    $> ./RPN ""
    Error
```

### small example
```ini
[1 2 + 3 -] becomes [1 + 2 - 3]
[4 5 * 6 \ 7 +] becomes [4 * 5 / 6 + 7]
```

# mental aproach

- we will get the formula as one string as argument.
- validate the string and throw exception if character is:
    - not digit `0 - 9`
    - not an operation `-, +, *, /`
- loop throw the string
    - if number insert push it to the stack
    - if operator
        - if stack contains one number throw exception
        - pop two numbers from the stack and execute the operation on them
        - push the result to the stack
- if the stack left with more them one number throw exception
- else that one number is your result.

```ini
Input : 8 9 * 9 - 9 - 9 - 4 - 1 +

┌───────┬────────┬───────────────┬──────────────────────┐
│ Token │ Action │ Operation     │ Stack (bottom → top)  │
├───────┼────────┼───────────────┼──────────────────────┤
│  8    │ push   │               │ [ 8 ]                 │
│  9    │ push   │               │ [ 8, 9 ]               │
│  *    │ pop×2  │ 8 * 9  = 72   │ [ 72 ]                 │
│  9    │ push   │               │ [ 72, 9 ]              │
│  -    │ pop×2  │ 72 - 9 = 63   │ [ 63 ]                 │
│  9    │ push   │               │ [ 63, 9 ]              │
│  -    │ pop×2  │ 63 - 9 = 54   │ [ 54 ]                 │
│  9    │ push   │               │ [ 54, 9 ]              │
│  -    │ pop×2  │ 54 - 9 = 45   │ [ 45 ]                 │
│  4    │ push   │               │ [ 45, 4 ]              │
│  -    │ pop×2  │ 45 - 4 = 41   │ [ 41 ]                 │
│  1    │ push   │               │ [ 41, 1 ]              │
│  +    │ pop×2  │ 41 + 1 = 42   │ [ 42 ]                 │
└───────┴────────┴───────────────┴──────────────────────┘

Result: 42
```


# PmergeMe

task: sort a set of numbers using `merge insertion sort` algorithm

### steps
`[3, 4, 8 , 1 , 0, 6, 9]`

1) create pairs
    - if the list contains only one element return;
    - split the list into pairs `[3, 4], [8, 1], [0, 6], [9]`
    - sort those pairs `[3, 4], [1, 8], [0, 6], [9]`
    - from each pair put the smaller element into a list `loosers` and the bigger into `winners` list, and if any single element left store it in left over
        - `winners`: [4, 8, 6]
        - `loosers`: [3, 1, 0]
        - `leftover`: 9

2) recursion Point
    - call the recursion function with the `winners` as parameter

3) insertion phase
    - now it's time to insert the loosers into the return result of the recursion.
    - the algo says take a range of loosers and insert them backward tell done 
        - eg: `loosers`: [3, 1, 0]
        - 1- insert 3
        - 2- insert 0, 1
    - we will follow jakopstall sequence to get the range on each iteration. 
    - eg: first time range == 1, second will be 3, third will be 5, ...
    - **insert steps :**
        - find the insert position using binary search. to acheave O(log n)
        - each *looser* mapped to a *winner*
        - so the search range will be from *0* to the *pos of the pair winner*
        - use the **target = lower_bound(begin(), winner_pos, value)** to get where to insert the value
        - use **insert(target - 1, value)** and done
    - don't forget to insert the `leftover` from earlier 

4) return the result list;





