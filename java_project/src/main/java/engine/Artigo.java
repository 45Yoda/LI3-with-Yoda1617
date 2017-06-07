package engine;


public class Artigo{

    private String titulo; //titulo do artigo
    private long id;
    private TreeMap<Integer,Revisao> revisions;
    private double words;
    private double bytes;

    /**
     * Construtor vazio
     */
    public Artigo(){
        this.titulo = " ";
        this.id = 0;
        this.revisions = new TreeMap<Integer,Revisao>();
        this.words = 0;
        this.bytes = 0;
    }

    /**
     * Construtor por parametros
     */

    public Artigo(String titu, long iden,Revisao revi,double word, double byt){
        this.titulo = titu;
        this.id = iden;
        this.revisions = new TreeMap<Integer,Revisao>();
        this.revisions.put(revi.getId(),revi);
        this.words = word;
        this.bytes = byt;
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
    }

    //gets
    public String getTitulo(){
        return this.titulo;
    }

    public long getId(){
        return this.id;
    }

    public TreeMap<Revisao> getRevs(){
        TreeMap<Integer,Revisao> aux = new TreeMap<Integer,Revisao> ();
        for(Revisao r: this.revisions)
            aux.add(r);

        return aux;
    }

    public double getWords(){
        return this.words;
    }

    public double getBytes(){
        return this.bytes;
    }

    //sets
    public void setTitulo(String titu){
        this.titulo = titu;
    }

    public void setId(long iden){
        this.id = iden;
    }

    public void setRev(Revisao revi){
        for(Revisao r: revi)
            this.revisions.add(revi);
    }

    public void setWords(double word){
        this.words = word
    }

    public void setBytes(double byt){
        this.bytes = byt;
    }


    //Método clone
    public Artigo clone(){
        return new Artigo();
    }

    //Método equals
    public boolean equals(Object o){
        if(this==o) return true;
        if((o==null) || o.getClass() != this.getClass()) return false;
        Artigo ar = (Artigo) o;
        return ar.getTitulo().equals(titulo) &&
               ar.getId() == id &&
               ar.getRev().equals(rev) &&
               ar.getWords() == words &&
               ar.getBytes() == bytes;
    }

    //Método toString
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Titulo do Artigo: ").append(titulo).append("\n");
        sb.append("Id do Artigo: ").append(id).append("\n");
        //TODO ADicionar o to String da Revisao ?
        sb.append("Número de palavras: ").append(words).append("\n");
        sb.append("Número de bytes: ").append(bytes).append("\n");

        return sb.toString();
    }



    //Métodos auxiliares

    public int quantRevisions(){
        return this.revisions.size();
    }

    public void addRevision(Revision rev){
        this.revisions.add(rev);
    }

    public Revisao getRevisao(long idRev){
        for(Revisao r: this.revisions){
            if(r.getId() == idRev) return r;
        }
    }
    
}
