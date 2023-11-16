## Arbol de misma estructura

### DESCRIPTION:
Construta un me´todo en la clase ArbolBinario que reciba como argumento otro árbol binario y retorne verdadero su ambos árboles tienen la misma estructura (no es necesariamente los mismo valores). Ejemplo:

```
           9
         /   \
        1     7
      /   \
     0     2
     
           4
         /   \
        2     8
      /   \
     0     3

 Tienen la misma estructura
```

### SOLUTION
```
public boolean isSameStructure(ArbolBinario<T> arbol2){
    return isSameStructureRecurrente(this.raiz, arbol2.raiz);
}
    
private boolean isSameStructureRecurrente(Nodo nodo1, Nodo nodo2) {
    boolean condicion = true;
    if(nodo1.tieneHijoIzq()!= nodo2.tieneHijoIzq()){
        return false;
    }
    else if(nodo1.tieneHijoIzq()){
        condicion &= isSameStructureRecurrente(nodo1.hijoIzq, nodo2.hijoIzq);
    }
    if(nodo1.tieneHijoDer()!= nodo2.tieneHijoDer()){
        return false;
    }
    else if(nodo1.tieneHijoDer()){
        condicion &= isSameStructureRecurrente(nodo1.hijoDer, nodo2.hijoDer);
    }
    return condicion;
}
```