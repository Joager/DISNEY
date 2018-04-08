package weixin.elotrab;

import java.util.Random;

public class Principal {
	
	private static String gerarStringRandom() {
		String caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		Random random = new Random();
		StringBuilder sb = new StringBuilder();
		for (int x = 0; x < random.nextInt(10) + 3; x++) {
			sb.append(caracteres.charAt(random.nextInt(caracteres.length())));
		}
		String strfinal = sb.toString();
		return strfinal;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Random random = new Random();
		double randomFinal = 10000 + (10000 - 1000) * random.nextDouble();
		System.out.println("///////////////////////////////////////");
		System.out.println("sistema charmy de criacao de empregados");
		System.out.println("///////////////////////////////////////");
		System.out.println("Gerando empregado aleatorio numero 1");
		Empregado empregado1 = new Empregado(gerarStringRandom(), gerarStringRandom(), randomFinal); // 8492 e um magic number aleatorio
		System.out.println("Gerando empregado aleatorio numero 2");
		randomFinal = 10000 + (10000 - 1000) * random.nextDouble(); // resetando random.nextDouble
		Empregado empregado2 = new Empregado(gerarStringRandom(), gerarStringRandom(), randomFinal);
	}

}
