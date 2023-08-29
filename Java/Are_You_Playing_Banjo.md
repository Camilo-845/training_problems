## Are You Playing Banjo?

### DESCRIPTION:
Create a function which answers the question "Are you playing banjo?".
If your name starts with the letter "R" or lower case "r", you are playing banjo!

The function takes a name as its only argument, and returns one of the following strings:

```
name + " plays banjo" 
name + " does not play banjo"
Names given are always valid strings.
```

### SOLUTION

```
public class Banjo {
  public static String areYouPlayingBanjo(String name) {
    if(name.toUpperCase().substring(0,1).equals("R")){
          return name+" plays banjo";
    }
    else{
        return name + " does not play banjo";
    }
  }
}
```