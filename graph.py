import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def crea_grafico_ODE(nome_file):
    """
    Legge un file CSV contenente t, x0, x1 e genera due grafici:
    1. Evoluzione temporale di x0 e x1.
    2. Traiettoria nello spazio delle fasi (x1 vs x0).

    Args:
        nome_file (str): Il percorso del file CSV.
    """
    
    try:
        # 1. Lettura dei dati
        df = pd.read_csv(nome_file)
    except FileNotFoundError:
        print(f"Errore: Il file '{nome_file}' non è stato trovato.")
        return
    except Exception as e:
        print(f"Errore durante la lettura del file: {e}")
        return

    # Verifichiamo che le colonne necessarie siano presenti
    if not all(col in df.columns for col in ['t', 'x0', 'x1']):
        print("Errore: Il file CSV deve contenere le colonne 't', 'x0', e 'x1'.")
        return

    # Inizializzazione della figura con due subplot affiancati
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))
    fig.suptitle(f"Analisi dei dati dall'equazione differenziale (File: {nome_file})", fontsize=16)

    # --- Subplot 1: Evoluzione Temporale ---
    
    # Plot di x0 in funzione del tempo
    ax1.plot(df['t'], df['x0'], label='$x_0(t)$', color='blue')
    
    # Plot di x1 in funzione del tempo
    ax1.plot(df['t'], df['x1'], label='$x_1(t)$', color='red', linestyle='--')
    
    ax1.set_xlabel("Tempo (t)")
    ax1.set_ylabel("Variabili dipendenti ($x_0, x_1$)")
    ax1.set_title("Evoluzione Temporale delle Variabili")
    ax1.grid(True, linestyle=':', alpha=0.6)
    ax1.legend()

    # --- Subplot 2: Spazio delle Fasi (Il Vincolo) ---
    
    # Plot di x1 in funzione di x0
    ax2.plot(df['x0'], df['x1'], color='purple', linewidth=2, label='Traiettoria')
    
    # Aggiungiamo un marker per il punto iniziale
    ax2.plot(df['x0'].iloc[0], df['x1'].iloc[0], 'go', markersize=8, label='Inizio (t=0)')
    
    # Aggiungiamo frecce per indicare la direzione del tempo
    # Usiamo un campionamento per non intasare il grafico
    n_points = len(df)
    stride = max(1, n_points // 8)  # Disegna circa 8 frecce
    
    for i in range(0, n_points - stride, stride):
        x_start = df['x0'].iloc[i]
        y_start = df['x1'].iloc[i]
        dx = df['x0'].iloc[i + stride] - x_start
        dy = df['x1'].iloc[i + stride] - y_start
        
        # Disegna la freccia
        ax2.arrow(x_start, y_start, dx, dy, 
                  head_width=0.05, head_length=0.08, 
                  fc='gray', ec='gray', alpha=0.5, length_includes_head=True)

    ax2.set_xlabel("$x_0$")
    ax2.set_ylabel("$x_1$")
    ax2.set_title("Spazio delle Fasi (Traiettoria su Vincolo)")
    
    # Forziamo gli assi ad avere la stessa scala per visualizzare correttamente il cerchio
    max_val = max(df['x0'].abs().max(), df['x1'].abs().max()) * 1.1
    ax2.set_xlim(-max_val, max_val)
    ax2.set_ylim(-max_val, max_val)
    ax2.set_aspect('equal', adjustable='box') # Essenziale per mantenere le proporzioni
    
    ax2.grid(True, linestyle=':', alpha=0.6)
    ax2.legend()
    
    # Mostra i grafici
    plt.tight_layout(rect=[0, 0.03, 1, 0.95]) # Aggiusta lo spazio per il titolo principale
    plt.show()

# --- Esecuzione ---
if __name__ == '__main__':
    # Assicurati che il file 'dati_simulazione.csv' esista nella stessa directory
    nome_file_input = 'ode.txt'
    crea_grafico_ODE(nome_file_input)