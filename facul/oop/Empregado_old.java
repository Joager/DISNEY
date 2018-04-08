package com.cubesouls;

public class Empregado {
	
	private String[] nomes = new String[2];
	private double salario = 0.0;
	
	protected void setNome(Empregado e, String nome, int nomesobre) {
		if (nomesobre > 1 || nomesobre < 0) {
			System.out.println("Erro! O inteiro <nomesobre> precisa ser 0 (nome) ou 1 (sobrenome)!");
		}
		else {
			this.nomes[nomesobre] = nome;
		}
	}
	
	protected String getNome(Empregado e, String nome, int nomesobre) {
		if (nomesobre > 1 || nomesobre < 0) {
			System.out.println("Erro! O inteiro <nomesobre> precisa ser 0 (nome) ou 1 (sobrenome)!");
			return "Erro!";
		}
		else {
			return this.nomes[nomesobre];
		}
	}
	
	
	protected void setSalario(Empregado e, double sal) {
		this.salario = sal;
	}
	
	protected double getSalario(Empregado e) {
		return this.salario;
	}
	
}

