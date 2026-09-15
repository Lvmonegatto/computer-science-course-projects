import { useState } from "react";

function Botao({ display, onClick }) {
  const estilo = {
    width: "120px",
    height: "35px",
    fontSize: "16px"
  };

  return (
    <button style={estilo} onClick={onClick}>
      {display}
    </button>
  );
}

function Mensagem() {
  const estilo = {
    display: "flex",
    justifyContent: "center",
    alignItems: "center",
    fontSize: "22px",
    fontWeight:"bold",
    fontFamily:"Times New Roman"
  };

  return (
    <p style={estilo}>
      Tente adivinhar o número de 0 a 99
    </p>
  );
}

function Adivinhacao() {
  const [numero, setNumero] = useState("");
  const [sorteado] = useState(Math.floor(Math.random() * 100));
  const [mensagem, setMensagem] = useState("");

  function verificar() {
    if (Number(numero) < 0 || Number(numero) > 99) {
      setMensagem("Somente números de 0 a 99 podem ser inseridos");
    } 
    else if (Number(numero) === sorteado) {
      setMensagem("Parabéns, número correto");
    } 
    else if (Number(numero) < sorteado) {
      setMensagem("Tente um número maior");
    } 
    else {
      setMensagem("Tente um número menor");
    }
  }

  const estilo_container = {
    display: "flex",
    justifyContent: "center",
    alignItems: "center",
    height: "100vh",
  };

  const estilo = {
    width: "400px",
    backgroundColor: "gray",
    padding: "15px",
    textAlign: "center",
  };

  const estilo_quadro = {
    width: "320px",
    height: "35px",
    fontSize: "20px",
    textAlign: "center",
  };

  const estilo_mensagem = {
    marginTop: "25px",
    backgroundColor: mensagem === "Parabéns, número correto" ? "green" : "red",
    color: "white",
    padding: "10px",
    fontSize: "18px",
    fontWeight: "bold",
  };

  return (
    <div style={estilo_container}>
      <div style={estilo}>
        <Mensagem />
        <input
          type="number"
          value={numero}
          onChange={(e) => setNumero(e.target.value)}
          style={estilo_quadro}
        />

        <Botao display="Clique Aqui" onClick={verificar} />

        <div style={estilo_mensagem}>
          {mensagem}
        </div>

      </div>
    </div>
  );
}

function App() {
  document.body.style.backgroundColor = "lightblue";

  return (
    <div>
      <Adivinhacao />
    </div>
  );
}

export default App;