## Abbreviate a Two Word Name
### DESCRIPTION:
Write a function to convert a name into initials. This kata strictly takes two words with one space in between them.

The output should be two capital letters with a dot separating them.

It should look like this:

Sam Harris => S.H

patrick feeney => P.F
### SOLUTION:
```
public class AbbreviateTwoWords {

  public static String abbrevName(String name) {
    String initials = "";
    String[] strArr = name.split(" ");
    initials += strArr[0].substring(0,1).toUpperCase();
    for( int i = 1; i < strArr.length; i++){
      initials += "."+ strArr[i].substring(0,1).toUpperCase();
    }
    return initials;
  }
}
```