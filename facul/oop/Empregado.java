package weixin.elotrab;

public class Empregado {
	private String primeiroNome;
	private String sobrenome;
	private double salario;
	
	public Empregado(String primeiroNome, String sobrenome, double salario) {
		this.primeiroNome = primeiroNome;
		this.sobrenome = sobrenome;
		if (salario <= 0) {
			throw new IllegalArgumentException("Erro! O salario especificado (" + salario + ") e menor ou igual a zero!\n"); 
		}
		else {
			this.salario = salario;
		}
		
	}
	
	public String getPrimeiroNome() {
		return primeiroNome;
		
	}
	
	public void setPrimeiroNome(String nome) {
		this.primeiroNome = nome;
	}
	
	public String getSobrenome() { 
		return sobrenome;
		
	}
	
	public void setSobrenome(String nome) {
		this.sobrenome = nome;
	}
	
	public double getSalario() {
		return salario;
		
	}
	
	public void setSalario(double salario) {
		this.salario = salario;
	}
}
