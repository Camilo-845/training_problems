## Reversed sequence

### DESCRIPTION:
Build a function that returns an array of integers from n to 1 where n>0.

```
Example : n=5 --> [5,4,3,2,1]
```

### SOLUTION: 
```
public class Sequence{

  public static int[] reverse(int n){
    int[] arr =  new int[n];
    for (int i = n; i>=1; i--){
      arr[n-i] = i;
    }
    return arr;
  }

}
```