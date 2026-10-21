const fs = require('fs');
const filePath = 'C:/Users/Dell/.gemini/antigravity/scratch/task4-bed-elevation-control/generate_pdf.js';
let code = fs.readFileSync(filePath, 'utf8');

// Update cover info
const oldInfo = "  ['Simulator', 'Wokwi (ESP32 DevKit-C v4)'],";
const newInfo = "  ['Simulator', 'Wokwi (ESP32 DevKit-C v4)'],\n  ['Live Wokwi URL', 'https://wokwi.com/projects/478424473823858689'],";

code = code.replace(oldInfo, newInfo);

// Add Section 1.5 portfolio table
const targetAnchor = "h2('1.4 Key Features (from smart_bed.ino)');";
const portfolioSection = `h2('1.5 Wokwi Projects Portfolio (All 4 Internship Tasks)');
body('The Smart Hospital IoT system was developed across four progressive tasks during the ElevanceSkills internship:');
table(
  ['Task', 'Project Title', 'Live Wokwi Simulation Link'],
  [
    ['Task 1', 'Multi-Sensor Expansion (FreeRTOS)', 'https://wokwi.com/projects/472146856163278849'],
    ['Task 2', 'Dual-Role IoT Monitoring System', 'https://wokwi.com/projects/470079753951045633'],
    ['Task 3', 'Smart Medication Dosage System', 'https://wokwi.com/projects/478395139061374977'],
    ['Task 4', 'Intelligent Remote Bed Elevation', 'https://wokwi.com/projects/478424473823858689'],
  ],
  [55, 215, 265]
);

`;

code = code.replace(targetAnchor, portfolioSection + targetAnchor);

// Update signature page
const oldSig = "  ['Simulator', 'Wokwi (ESP32 DevKit-C v4)'],";
const newSig = "  ['Simulator', 'Wokwi (ESP32 DevKit-C v4)'],\n  ['Wokwi Project URL', 'https://wokwi.com/projects/478424473823858689'],";
code = code.replace(oldSig, newSig);

fs.writeFileSync(filePath, code, 'utf8');
console.log('generate_pdf.js updated successfully!');
