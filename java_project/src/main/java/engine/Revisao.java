package engine;

public class Revisao{

    private long id;
    private String timestamp;

    /**
     * Construtor vazio
     */
    public Revisao(){
        id = 0;
        timestamp="";
    }

    /**
     * Construtor por parametros
     */

    public Revisao(long iden){
        this.id = iden;
    }

    /**
     * Construtor por cópia
     */
    public Revisao(Revisao c){
        id = c.getId();
    }

    //gets
    public long getId(){
        return this.id;
    }

    //sets
    public void setId(long iden){
        this.id = iden;
    }

    //Método clone
    public Revisao clone(){
        return new Revisao();
    }

    //Método equals
    public boolean equals(Object o){
        if(this==o) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        Revisao rev = (Revisao) o;
        return rev.getId() == id;
    }

    //Método toString
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Id da revisão: ").append(id).append("\n");

        return sb.toString();
    }


}
