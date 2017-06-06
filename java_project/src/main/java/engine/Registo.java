package engine;

import java.util.Map;
import java.util.TreeMap;

public class Registo{

    private CatArtigos cArt;
    private CatContrib cCont;

    /**
    * Construtor vazio
    */
    public Registo(){
        cArt = new CatArtigos();
        cCont = new CatContrib();
    }

    /**
     * Construtor por parâmetros
     */
     public Registo(CatArtigos cArti,CatContrib cContri){
         this.cArt = cArti;
         this.cCont = cContri;
     }

     /**
      * Construtor por cópia
      */
     public Registo(Registo r){
         cArt = r.getCatArt();
         cCont = r.getCatCont();
     }

     //gets
     public CatArtigos getCatArt(){
         return this.cArt.clone();
     }

     public CatContrib getCatCont(){
         return this.cCont.clone();
     }

     //sets
     public void setCatArt(CatArtigos cArti){
         this.cArt = cArti;
     }

     public void setCatCont(CatContrib cContri){
         this.cCont = cContri;
     }

     //Método clone;
     public Registo clone(){
         return new Registo();
     }

     //Método equals
     public boolean equals(Object o){
         if(o == this) return true;
         if(o == null || o.getClass() != o.getClass()) return false;
         Registo r = (Registo) o;
         return r.getCatArt().equals(cArt) &&
                r.getCatCont().equals(cCont);
     }


}
