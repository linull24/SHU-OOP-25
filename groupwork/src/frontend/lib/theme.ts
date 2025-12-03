import { argbFromHex, themeFromSourceColor, applyTheme } from '@material/material-color-utilities';

export function applyBlueTheme() {
  const theme = themeFromSourceColor(argbFromHex('#1976D2'));
  applyTheme(theme, { target: document.documentElement, dark: false });
}
