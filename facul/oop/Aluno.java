
public class Aluno {
	private int matricula;
	private String nome;
	private double[] notas = new double[4]; //1a prova, 2a prova, 1o trabalho, 2o trabalho
	
	public int getMatricula() {
		return this.matricula;
	}
	
	public String getNome() {
		return this.nome;
	}
	
	public double verNota(int tipo) {
		if (tipo > 3 || tipo < 0) {
			throw new IllegalArgumentException("Erro! O valor " + tipo + " nao e um inteiro de 0 a 3! Verifique a documentacao\n");
		}
		return this.notas[tipo];
	}
	
	public double media() {
		double media = 0;
		double x[] = new double[4]; // criar um clone
		for (int y = 0; y < notas.length; y++) {
			if (y >= 0 && y < 2) {
				x[y] = this.notas[y] * 0.7; // provas 1 e 2
				media += x[y];
			}
			else {
				x[y] = this.notas[y] * 0.3; // trabalhos 1 e 2
				media += x[y];
			}
		}
		media = media / notas.length;
		return media;
	}
}
