import os

# Caminho para o arquivo .env no diretório atual do projeto
env_file = os.path.join(os.getcwd(), ".env")

# Verifica se o arquivo .env realmente existe antes de tentar ler
if os.path.exists(env_file):
    with open(env_file, "r") as f:
        for line in f:
            # Remove espaços em branco nas pontas da linha
            line = line.strip()
            
            # Ignora linhas vazias ou que sejam comentários (começam com #)
            if line and not line.startswith("#"):
                # Divide a linha apenas no primeiro "=" encontrado
                key, val = line.split("=", 1)
                
                # Limpa espaços e remove aspas extras (simples ou duplas) do valor
                key = key.strip()
                val = val.strip().strip('"').strip("'")
                
                # Injeta a variável temporariamente na memória do ambiente de compilação
                os.environ[key] = val
