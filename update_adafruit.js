const fs = require('fs');
const filePath = 'C:/Users/Dell/.gemini/antigravity/scratch/task4-bed-elevation-control/generate_pdf.js';
let code = fs.readFileSync(filePath, 'utf8');

// Replace cover info to add Adafruit IO
const oldInfo = "  ['Live Wokwi URL', 'https://wokwi.com/projects/478424473823858689'],";
const newInfo = "  ['Live Wokwi URL', 'https://wokwi.com/projects/478424473823858689'],\n  ['Cloud Dashboard', 'https://io.adafruit.com/MOSAB_SAIF/dashboards/default'],";
code = code.replace(oldInfo, newInfo);

// Update section 1.5 portfolio table
const oldPortfolio = `table(
  ['Task', 'Project Title', 'Live Wokwi Simulation Link'],
  [
    ['Task 1', 'Multi-Sensor Expansion (FreeRTOS)', 'https://wokwi.com/projects/472146856163278849'],
    ['Task 2', 'Dual-Role IoT Monitoring System', 'https://wokwi.com/projects/470079753951045633'],
    ['Task 3', 'Smart Medication Dosage System', 'https://wokwi.com/projects/478395139061374977'],
    ['Task 4', 'Intelligent Remote Bed Elevation', 'https://wokwi.com/projects/478424473823858689'],
  ],
  [55, 215, 265]
);`;

const newPortfolio = `table(
  ['Task', 'Project Title', 'Live Wokwi Simulation Link'],
  [
    ['Task 1', 'Multi-Sensor Expansion (FreeRTOS)', 'https://wokwi.com/projects/472146856163278849'],
    ['Task 2', 'Dual-Role IoT Monitoring System', 'https://wokwi.com/projects/470079753951045633'],
    ['Task 3', 'Smart Medication Dosage System', 'https://wokwi.com/projects/478395139061374977'],
    ['Task 4', 'Intelligent Remote Bed Elevation', 'https://wokwi.com/projects/478424473823858689'],
  ],
  [55, 215, 265]
);

h2('1.6 Cloud IoT Dashboard Link');
body('For external public evaluation without local setup, a cloud dashboard is hosted on Adafruit IO:');
bullet('Live Public Dashboard URL: https://io.adafruit.com/MOSAB_SAIF/dashboards/default');
bullet('Local Nurse Station Dashboard: Node-RED on http://localhost:1880/ui (demonstrated in video)');
`;

code = code.replace(oldPortfolio, newPortfolio);

// Update signature page
const oldSig = "  ['Wokwi Project URL', 'https://wokwi.com/projects/478424473823858689'],";
const newSig = "  ['Wokwi Project URL', 'https://wokwi.com/projects/478424473823858689'],\n  ['Cloud Dashboard', 'https://io.adafruit.com/MOSAB_SAIF/dashboards/default'],";
code = code.replace(oldSig, newSig);

fs.writeFileSync(filePath, code, 'utf8');
console.log('generate_pdf.js updated with Adafruit IO links!');
