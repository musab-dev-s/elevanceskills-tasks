const fs = require('fs');
const files = [
  'D:/Downloads/elevanceskills intern.pdf',
  'D:/Downloads/elevanceskills IOT.pdf'
];

files.forEach(p => {
  if (fs.existsSync(p)) {
    const content = fs.readFileSync(p, 'utf8');
    const urls = content.match(/https?:\/\/[^\s\)\>\]\"\'<]+/gi) || [];
    console.log('=== URLS in ' + p + ' ===');
    console.log([...new Set(urls)]);
    
    // Also look for keywords like forms.gle, forms.google, etc.
    const formMatches = content.match(/[a-zA-Z0-9_\-\.\/]+(?:form|submit|eval)[a-zA-Z0-9_\-\.\/]*/gi) || [];
    console.log('=== Form keywords in ' + p + ' ===');
    console.log([...new Set(formMatches)].slice(0, 10));
  }
});
