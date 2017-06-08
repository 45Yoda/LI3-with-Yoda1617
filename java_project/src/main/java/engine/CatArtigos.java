package engine;

import java.util.TreeMap;
import java.util.Map;
import java.io.Serializable;

public class CatArtigos implements Serializable{

    private Map<Long,Artigo> artigos;

    /**
     * Construtor vazio
     */
    public CatArtigos(){
        artigos = new TreeMap<Long,Artigo>();
    }

    /**
     * Construtor por parâmetros
     */
    public CatArtigos(TreeMap<Long,Artigo> catalogo){
        this.artigos = catalogo;
    }

    /**
     * Construtor por cópia
     */
     public CatArtigos(CatArtigos c){
         artigos = c.getCatalogo();
     }

     //gets

     public Map<Long,Artigo> getCatalogo(){
        return this.artigos;
    }

    //sets

    public void setCatalogo(TreeMap<Long,Artigo> artigos){
        this.artigos = new TreeMap<Long,Artigo>();
        for(Map.Entry<Long,Artigo> entry: artigos.entrySet())
            this.artigos.put(entry.getKey(),entry.getValue());
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
        this.artigos.put(art.getId(),art);
    }

    //Função que descobre se existe um Artigo especifico
    public boolean existeArtigo(Long idArt){
        return this.artigos.containsKey(idArt);
    }

    public void clean(){
        this.artigos.clear();
    }

    public Artigo getArtigo(Long idArt){
        return this.artigos.get(idArt);
    }
}
