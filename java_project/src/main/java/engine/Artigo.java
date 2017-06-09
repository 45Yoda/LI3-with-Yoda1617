package engine;

import java.util.Map;
import java.util.TreeMap;


public class Artigo{

    private String titulo; //titulo do artigo
    private long id;
    private TreeMap<Long,Revisao> revisions;
    private long words;
    private long bytes;
    private int flag;

    /**
     * Construtor vazio
     */
    public Artigo(){
        this.titulo = " ";
        this.id = 0;
        this.revisions = new TreeMap<Long,Revisao>();
        this.words = 0;
        this.bytes = 0;
        this.flag=0;
    }

    /**
     * Construtor por parametros
     */

    public Artigo(String titu, long iden,Revisao revi,long word, long byt, int n){
        this.titulo = titu;
        this.id = iden;
        this.revisions = new TreeMap<Long,Revisao>();
        this.revisions.put(revi.getId(),revi);
        this.words = word;
        this.bytes = byt;
        this.flag=n;
    }

    /**
     * Construtor por cópia
     */

    public Artigo(Artigo c){
        this.titulo = c.getTitulo();
        this.id = c.getId();
        this.revisions = c.getRevs();
        this.words = c.getWords();
        this.bytes = c.getBytes();
        this.flag = c.getFlag();
    }

    //gets
    public String getTitulo(){
        return this.titulo;
    }

    public long getId(){
        return this.id;
    }

    public TreeMap<Long,Revisao> getRevs(){
        TreeMap<Long,Revisao> aux = new TreeMap<Long,Revisao> ();
        for(Map.Entry <Long,Revisao> r: this.revisions.entrySet())
            aux.put(r.getKey(),r.getValue());

        return aux;
    }

    public long getWords(){
        return this.words;
    }

    public long getBytes(){
        return this.bytes;
    }

    public int getFlag() {
        return this.flag;
    }

    //sets
    public void setTitulo(String titu){
        this.titulo = titu;
    }

    public void setId(long iden){
        this.id = iden;
    }

    public void setRev(Revisao revi){
        this.revisions.put(revi.getId(),revi);
    }

    public void setWords(long word){
        this.words = word;
    }

    public void setBytes(long byt){
        this.bytes = byt;
    }

    public void setFlag(int n) {
        this.flag=n;
    }

    //Método clone
    public Artigo clone(){
        return new Artigo(this);
    }

    //Método equals
    public boolean equals(Object o){
        if(this==o) return true;
        if((o==null) || o.getClass() != this.getClass()) return false;
        Artigo ar = (Artigo) o;
        return ar.getTitulo().equals(titulo) &&
               ar.getId() == id &&
               ar.getRevs().equals(revisions) &&
               ar.getWords() == words &&
               ar.getBytes() == bytes &&
               ar.getFlag() == flag;
    }

    //Método toString
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Titulo do Artigo: ").append(titulo).append("\n");
        sb.append("Id do Artigo: ").append(id).append("\n");
        sb.append("Revisões:").append(revisions.toString()).append("\n");
        sb.append("Número de palavras: ").append(words).append("\n");
        sb.append("Número de bytes: ").append(bytes).append("\n");
        sb.append("Número de vezes que artigo aparece: ").append(flag).append("\n");

        return sb.toString();
    }



    //Métodos auxiliares

    public int quantRevisions(){
        return this.revisions.size();
    }

    public void addRevisao(Revisao rev){
        this.revisions.put(rev.getId(),rev);
    }

    public Revisao getRevisao(long idRev){
        return this.revisions.get(idRev);
    }

    public boolean existeRevisao(long idRev){
        return this.revisions.containsKey(idRev);
    }

    public void incrFlag() {
        this.flag++;
    }
}
