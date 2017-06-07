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

    public Revisao(long iden,String time){
        this.id = iden;
        this.timestamp = time;
    }

    /**
     * Construtor por cópia
     */
    public Revisao(Revisao c){
        this.id = c.getId();
        this.timestamp=c.getTimestamp();
    }

    //gets
    public long getId(){
        return this.id;
    }

    public String getTimestamp() {
        return this.timestamp;
    }

    //sets
    public void setId(long iden){
        this.id = iden;
    }

    public void setTimestamp(String time) {
        this.timestamp = time;
    }

    //Método clone
    public Revisao clone(){
        return new Revisao(this);
    }

    //Método equals
    public boolean equals(Object o){
        if(this==o) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        Revisao rev = (Revisao) o;
        return rev.getId() == id &&
               rev.getTimestamp() == timestamp;
    }

    //Método toString
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Id da revisão: ").append(id).append("\n");
        sb.append("Timestamp da revisão: ").append(timestamp).append("\n");
        return sb.toString();
    }


}
