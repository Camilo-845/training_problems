## Monticulo por minimos

### DESCRIPTION: 
Un árbol binario cumple la propiedad de montículo por minimos si cada nodo contiene un valor menor o tigual al de sus hijos. Contruya un método en la clase ArbolBinario que reciba como argumento un java.util.Comparaton<T> y retorne verdadero si el árbol cumple con esa propiedad y falso en caso contrario.

Ejemplos: 
```
           3
         /   \
        4     5
      /   \
     8     12

    Retorna True

           8
         /   \
        2     4
      /   \
     8     1
    
    Retorna False
```

### SOLUTION
```
public boolean isMonticuloMinimo(Comparator<T> comparar){
    return isMonticuloMinimorecursivo(comparar,this.raiz);
}

private boolean isMonticuloMinimorecursivo(Comparator<T> comparar, Nodo nodo) {
    boolean condicion = true;
    if(nodo.tieneHijoIzq()){
        if(comparar.compare(nodo.getInfo(), nodo.hijoIzq.getInfo())== 1){
            return false;
        }
        else{
            condicion &= isMonticuloMinimorecursivo(comparar, nodo.hijoIzq);
        }
    }
    if(nodo.tieneHijoDer()){
        if(comparar.compare(nodo.getInfo(), nodo.hijoDer.getInfo())== 1){
            return false;
        }
        else{
            condicion &= isMonticuloMinimorecursivo(comparar, nodo.hijoDer);
        }
    }
    return condicion;
}
```
