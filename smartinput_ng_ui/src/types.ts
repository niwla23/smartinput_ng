export interface EffectOptions {
  current: string | number | boolean
  default: string | number | boolean
  friendly_name: string
  max?: number,
  min?: number,
  type: "int" | "color" | "boolean"
}

export interface Effect {
  active: boolean
  friendlyName: string
  options: { [name: string]: EffectOptions }
}

export interface EffectList {
  [name: string]: Effect
}