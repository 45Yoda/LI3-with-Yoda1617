package engine;

import java.util.TreeMap;
import java.util.Map;
import java.util.Serializable;

public class CatArtigos implements Serializable{

    private Map<Integer,Artigo> artigos;

    /**
     * Construtor vazio
     */
    public CatArtigos(){
        artigos = new TreeMap<Integer,Artigo>();
    }

    /**
     * Construtor por parâmetros
     */
    public CatArtigos(TreeMap<Integer,Artigo> catalogo){
        this.artigos = catalogo;
    }

    /**
     * Construtor por cópia
     */
     public CatArtigos(CatArtigos c){
         artigos = c.getCatalogo();
     }

     //gets

     public Map<Integer,Artigo> getCatalogo(){
         artigos = new TreeMap<Integer,Artigo>();

         for(Map.Entry<Integer,Artigo> entry: this.artigos.entrySet())
            artigos.put(entry.getKey(),entry.getValue().clone());

        return artigos;
    }

    //sets

    public void setCatalogo(TreeMap<Integer,Artigo> artigos){
        this.artigos = new TreeMap<Integer,Artigo>();
        for(Map.Entry<Integer,Artigo> entry: artigos.entrySet())
            this.artigos.put(entry.getKey(),entry.getValue().clone());
    }

    //Método clone
    public CatArtigos clone(){
        return new CatArtigos();
    }

    //Método equals
    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        CatArtigos ca = (CatArtigos) o;
        return ca.getCatalogo().equals(artigos);
    }

    //Métodos auxiliares

    //Conta artigos
    public long contaArt(){
        return this.artigos.size();
    }

    //Função que insere um artigo no catálogo
    public void insereArtigo(Artigo art){
        this.artigos.put(art.getId(),art.clone());
    }

    //Necessário ???? REVIEW
    public void removeArtigo(Artigo art){
        this.artigos.remove(art.getId());
    }

    //Função que descobre se existe um Artigo especifico
    public boolean existeArtigo(Artigo art){
        this.artigo.get(art.getId()).containsValue(art);
    }

    public void clean(){
        this.artigos.clear();
    }
}
