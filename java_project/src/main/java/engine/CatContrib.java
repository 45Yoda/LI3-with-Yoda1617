package engine;

import java.util.TreeMap;
import java.util.Map;
import java.io.Serializable;



public class CatContrib implements Serializable{

    private Map<Long,Contribuidor> contribuidor;

    /**
     * Construtor vazio
     */
    public CatContrib(){
        contribuidor = new TreeMap<Long,Contribuidor>();
    }

    /**
     * Construtor por parâmetros
     */
    public CatContrib(TreeMap<Long,Contribuidor> catalogo){
        this.contribuidor = catalogo;
    }

    /**
     * Construtor por cópia
     */
    public CatContrib(CatContrib c){
        contribuidor = c.getCatalogo();
    }

    //gets
    public Map<Long,Contribuidor> getCatalogo(){
        contribuidor = new TreeMap<Long,Contribuidor>();

        for(Map.Entry<Long,Contribuidor> entry: this.contribuidor.entrySet())
            contribuidor.put(entry.getKey(),entry.getValue().clone());

        return contribuidor;
    }

    //sets
    public void setCatalogo(TreeMap<Long,Contribuidor> contribuidor) {
        contribuidor = new TreeMap<Long,Contribuidor>();
        for(Map.Entry<Long,Contribuidor> entry: contribuidor.entrySet())
            this.contribuidor.put(entry.getKey(),entry.getValue().clone());
    }

    //Método clone
    public CatContrib clone(){
        return new CatContrib(this);
    }

    //Método equals
    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        CatContrib cc = (CatContrib) o;
        return cc.getCatalogo().equals(contribuidor);
    }


    //Métodos auxiliares

    //Função que insere um contribuidor no catálogo

    public void insereContribuidor(Contribuidor cont){
        this.contribuidor.put(cont.getId(),cont.clone());
    }


    //Necessário ???? REVIEW
    public void removeContribuidor(Contribuidor cont){
        this.contribuidor.remove(cont.getId());
    }

    //Função que descobre se existe um Contribuidor especifico
    public boolean existeContribuidor(Contribuidor cont){
            return this.contribuidor.containsValue(cont);
    }

    public void clean(){
        this.contribuidor.clear();
    }
}
