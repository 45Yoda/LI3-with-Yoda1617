package engine;

public class Contribuidor{

    private String username; //Username do Contribuidor
    private int cont; //Contribuições do Contribuidor
    private long id; // Id de contribuidor

    //Construtores
    public Contribuidor(){
        username = " ";
        cont = 0;
        id = 0;
    }

    public Contribuidor(String user, int contrib, long iden){
        this.username = user;
        this.cont = contrib;
        this.id = iden;
    }

    public Contribuidor(Contribuidor c){
        username = c.getUsername();
        cont = c.getCont();
        id = c.getId();
    }

    //gets
    public String getUsername(){
        return this.username;
    }

    public int getCont(){
        return this.cont;
    }

    public long getId(){
        return this.id;
    }

    //sets
    public void setUsername(String user){
        this.username = user;
    }

    public void setCont(int contrib){
        this.cont = contrib;
    }

    public void setId(long iden){
        this.id = iden;
    }

    //Método clone
    public Contribuidor clone(){
        return new Contribuidor();
    }

    //Método equals
    public boolean equals(Object o){
        if(this==o) return true;
        if((o==null) || o.getClass() != this.getClass()) return false;
        Contribuidor c = (Contribuidor) o;
        return c.getUsername().equals(username) &&
               c.getCont() == cont              &&
               c.getId() == id;
    }

    //Método toString
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Username do Contribuidor: ").append(username).append("\n");
        sb.append("Contribuições do Contribuidor: ").append(cont).append("\n");
        sb.append("Id do Contribuidor: ").append(id).append("\n");

        return sb.toString();
    }

    public void incrCont() {
        this.cont++;
    }
}
