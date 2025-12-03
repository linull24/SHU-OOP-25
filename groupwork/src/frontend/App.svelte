<script lang="ts">
  import './styles.css';
  import '@material/web/button/filled-button';
  import '@material/web/button/outlined-button';
  import '@material/web/textfield/filled-text-field';

  import { onMount } from 'svelte';
  import wasmModule from './wasm-inline.js';
  import mermaid from 'mermaid';
  import { applyBlueTheme } from './lib/theme';
  
  let list = null;
  let ready = false;
  let output = '';
  let value = '', insertId = '', deleteId = '', customId = '', targetId = '';
  let diagramEl;
  let showPositionInput = false;
  let positionTimeout = null;

  onMount(async () => {
    applyBlueTheme();
    mermaid.initialize({ 
      startOnLoad: false, 
      theme: 'base',
      flowchart: { curve: 'basis' },
      themeVariables: {
        primaryColor: '#1976D2',
        primaryTextColor: '#fff',
        primaryBorderColor: '#1565C0',
        lineColor: '#1976D2',
        secondaryColor: '#E3F2FD',
        tertiaryColor: '#90CAF9',
        mainBkg: '#1976D2',
        nodeBorder: '#1565C0',
        clusterBkg: '#E3F2FD',
        edgeLabelBackground: '#fff',
        primaryBorderRadius: '12px'
      }
    });
    list = new (await wasmModule()).LinkedList();
    ready = true;
    await new Promise(resolve => setTimeout(resolve, 0));
    refresh();
  });

  const validateId = (id) => {
    const num = parseInt(id);
    return (!id || isNaN(num) || num <= 0) ? -1 : num;
  };

  const insertHead = () => { list.insertHead(value, validateId(insertId)); value = ''; insertId = ''; refresh(); };
  const insertTail = () => { list.insertTail(value, validateId(insertId)); value = ''; insertId = ''; refresh(); };

  const handleInsertAfterHover = () => {
    showPositionInput = true;
    if (positionTimeout) clearTimeout(positionTimeout);
    positionTimeout = setTimeout(() => {
      showPositionInput = false;
    }, 2000);
  };
  
  const handlePositionInput = (e) => {
    targetId = e.target.value;
    if (positionTimeout) clearTimeout(positionTimeout);
    positionTimeout = setTimeout(() => {
      showPositionInput = false;
    }, 2000);
  };
  
  const quickInsertAfter = () => {
    const tid = validateId(targetId);
    if (tid > 0 && value) {
      list.insertAfterId(tid, value, validateId(customId));
      value = ''; customId = ''; targetId = '';
      showPositionInput = false;
      if (positionTimeout) clearTimeout(positionTimeout);
      refresh();
    }
  };
  

  const deleteNode = () => { list.deleteById(validateId(deleteId)); deleteId = ''; refresh(); };
  const reverse = () => { list.reverse(); refresh(); };
  const clear = () => { list.clear(); refresh(); };
  const sortById = () => { list.sortById(); refresh(); };
  const sortByValue = () => { list.sortByValue(); refresh(); };
  const refresh = async () => {
    const minVal = list.getMinValue(), maxVal = list.getMaxValue();
    output = `Count: ${list.count()} | ${minVal ? `Min: ${minVal} | Max: ${maxVal}` : 'N/A'} | Single Chain: ${list.isSingleChain()}`;
    if (diagramEl) {
      try {
        diagramEl.innerHTML = (await mermaid.render('d' + Date.now(), list.toMermaid())).svg;
        diagramEl.querySelectorAll('rect').forEach(r => { r.setAttribute('rx', '12'); r.setAttribute('ry', '12'); });
      } catch(e) { diagramEl.innerHTML = `<pre style="color: red;">${e}</pre>`; }
    }
  };
</script>

<main>
  <div class="header">
    <h1>Linked List</h1>
    <span class="status">{ready ? '● Ready' : '○ Loading...'}</span>
  </div>
  
  {#if ready}
    <div class="card">
      <div class="controls">
        <md-filled-text-field label="Custom ID (optional)" type="number" value={insertId} on:input={(e) => insertId = e.target.value}></md-filled-text-field>
        <md-filled-text-field label="Value" value={value} on:input={(e) => value = e.target.value}></md-filled-text-field>
        <div class="button-group">
          <md-filled-button on:click={insertHead}>Head</md-filled-button>
          <span class="divider"></span>
          <md-filled-button on:click={insertTail}>Tail</md-filled-button>
        </div>
        <div class="insert-after-wrapper" on:mouseenter={handleInsertAfterHover}>
          {#if showPositionInput}
            <md-filled-text-field 
              class="position-input" 
              label="Position" 
              type="number" 
              value={targetId} 
              on:input={handlePositionInput}
            ></md-filled-text-field>
          {/if}
          <md-filled-button on:click={quickInsertAfter}>Insert After</md-filled-button>
        </div>
      </div>
      <div class="controls">
        <md-filled-text-field label="Delete ID" type="number" value={deleteId} on:input={(e) => deleteId = e.target.value}></md-filled-text-field>
        <md-outlined-button on:click={deleteNode}>Delete</md-outlined-button>
        <md-outlined-button on:click={reverse}>Reverse</md-outlined-button>
        <md-outlined-button on:click={sortById}>Sort by ID</md-outlined-button>
        <md-outlined-button on:click={sortByValue}>Sort by Value</md-outlined-button>
        <md-outlined-button on:click={clear}>Clear</md-outlined-button>
      </div>
    </div>
    
    
    <div class="card">
      <div bind:this={diagramEl}></div>
    </div>
    
    <div class="card">
      <pre class="output">{output}</pre>
    </div>
  {/if}
</main>

<style>
  md-dialog form { display: flex; flex-direction: column; gap: 16px; padding: 20px 0; }
  .insert-after-wrapper { position: relative; display: flex; align-items: center; gap: 0.5rem; }
  .position-input { 
    width: 120px; 
    animation: slideIn 0.2s ease-out;
  }
  @keyframes slideIn {
    from { opacity: 0; transform: translateX(-10px); }
    to { opacity: 1; transform: translateX(0); }
  }
</style>
